#!/usr/bin/env python3
"""Run all jobs in a GitHub Actions workflow locally with act."""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path
from typing import Iterable, List

try:
    import yaml
except ModuleNotFoundError as error:
    print(
        "Missing dependency: PyYAML is required for workflow parsing.\n"
        "Install it for the interpreter running this script, e.g.:\n"
        "  python3 -m pip install pyyaml"
    )
    raise SystemExit(1) from error


class GitHubActionsLoader(yaml.SafeLoader):
    """YAML loader tuned for GitHub Actions workflow files."""


# Prevent YAML 1.1 boolean coercion for keys like "on", "off", "yes", "no".
# GitHub Actions treats these as plain strings.
GitHubActionsLoader.yaml_implicit_resolvers = {
    key: list(value) for key, value in yaml.SafeLoader.yaml_implicit_resolvers.items()
}
for key, resolvers in GitHubActionsLoader.yaml_implicit_resolvers.items():
    GitHubActionsLoader.yaml_implicit_resolvers[key] = [
        (tag, regexp) for (tag, regexp) in resolvers if tag != "tag:yaml.org,2002:bool"
    ]


def parse_workflow_jobs(workflow_file: Path) -> List[str]:
    """Extract top-level job IDs from a workflow using YAML parsing."""
    if not workflow_file.exists():
        raise FileNotFoundError(f"Workflow file not found: {workflow_file}")

    with workflow_file.open("r", encoding="utf-8", errors="replace") as infile:
        data = yaml.load(infile, Loader=GitHubActionsLoader)

    if not isinstance(data, dict):
        raise ValueError(f"Workflow root must be a mapping in {workflow_file}")

    jobs = data.get("jobs")
    if jobs is None:
        raise ValueError(
            f"Could not find a top-level 'jobs:' section in {workflow_file}"
        )

    if not isinstance(jobs, dict):
        raise ValueError(f"'jobs' must be a mapping in {workflow_file}")

    job_ids = [str(job_id) for job_id in jobs.keys()]
    return job_ids


def run_act_job(
    act_bin: str,
    workflow_file: Path,
    job_name: str,
    container_architecture: str,
    platform_map: str,
    passthrough_args: Iterable[str],
    dry_run: bool,
) -> bool:
    cmd: List[str] = [
        act_bin,
        "--container-architecture",
        container_architecture,
    ]

    if platform_map:
        cmd.extend(["-P", platform_map])

    cmd.extend(["-W", str(workflow_file), "-j", job_name])
    cmd.extend(passthrough_args)

    print(f"\nRunning job: {job_name}")
    print("Command:", " ".join(cmd))

    if dry_run:
        return True

    result = subprocess.run(cmd, check=False)
    if result.returncode == 0:
        print(f"✓ Successfully ran {job_name}")
        return True

    print(f"✗ Failed to run {job_name} (exit code: {result.returncode})")
    return False


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Run all jobs from a GitHub Actions workflow with act"
    )
    parser.add_argument(
        "--workflow-file",
        type=Path,
        default=Path(".github/workflows/ci.yml"),
        help="Workflow file to parse (default: %(default)s)",
    )
    parser.add_argument(
        "--job",
        action="append",
        default=[],
        help="Specific job ID to run (can be provided multiple times)",
    )
    parser.add_argument(
        "--list-jobs",
        action="store_true",
        help="List discovered jobs and exit",
    )
    parser.add_argument(
        "--continue-on-failure",
        action="store_true",
        help="Continue running remaining jobs if one fails",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print act commands without executing them",
    )
    parser.add_argument(
        "--act-bin",
        default="act",
        help="Path to act executable (default: %(default)s)",
    )
    parser.add_argument(
        "--container-architecture",
        default="linux/amd64",
        help="Value for act --container-architecture (default: %(default)s)",
    )
    parser.add_argument(
        "--platform-map",
        default="ubuntu-latest=catthehacker/ubuntu:act-latest",
        help="Value for act -P (default: %(default)s)",
    )
    parser.add_argument(
        "--act-arg",
        action="append",
        default=[],
        help="Extra argument to pass to act (can be repeated)",
    )
    return parser


def main(argv: List[str]) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    try:
        job_ids = parse_workflow_jobs(args.workflow_file)
    except (OSError, ValueError, yaml.YAMLError) as error:
        print(error)
        return 1

    if not job_ids:
        print(f"No jobs found in {args.workflow_file}")
        return 1

    selected_jobs = args.job if args.job else job_ids
    unknown_jobs = [job for job in selected_jobs if job not in job_ids]

    if unknown_jobs:
        print(f"Unknown job IDs: {', '.join(unknown_jobs)}")
        print(f"Available jobs: {', '.join(job_ids)}")
        return 1

    if args.list_jobs:
        print("Discovered jobs:")
        for job in job_ids:
            marker = "*" if job in selected_jobs else " "
            print(f"{marker} {job}")
        return 0

    print(f"Found {len(job_ids)} workflow job(s): {', '.join(job_ids)}")
    print(f"Running {len(selected_jobs)} job(s): {', '.join(selected_jobs)}")

    failed_jobs: List[str] = []

    for job_name in selected_jobs:
        ok = run_act_job(
            act_bin=args.act_bin,
            workflow_file=args.workflow_file,
            job_name=job_name,
            container_architecture=args.container_architecture,
            platform_map=args.platform_map,
            passthrough_args=args.act_arg,
            dry_run=args.dry_run,
        )
        if not ok:
            failed_jobs.append(job_name)
            if not args.continue_on_failure:
                break

    if failed_jobs:
        print(f"\n❌ {len(failed_jobs)} job(s) failed: {', '.join(failed_jobs)}")
        return 1

    print(f"\n✅ Successfully ran {len(selected_jobs)} job(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
