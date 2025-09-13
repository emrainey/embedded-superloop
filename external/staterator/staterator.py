#!/usr/bin/env python3

import os

# import re
import sys
import yaml
import jinja2
import typing
import argparse
from typing import Any, List, Dict, Optional
from jinja2 import Environment, FileSystemLoader

verbose: bool = False


def enum_states(states: List[Dict[str, str]]) -> str:
    """
    Generates the list of state values for all the states, and sub state levels (up to 4 levels deep).
    Takes the diction of states and substates and returns a list of states with nestings in the name and their values in single level
    Top level states are in the upper byte, next level states in the 2nd byte, and so on. There are up to 254 possible states in each level. 0 and 255 are reserved.
    (input)
    states:
        - name: A
          states:
            - name: B
              states:
            - name: C
        - name: B
          states:
            - name: A
            - name: B
    out:
        - name: A
          value: 0x01'00'00'00
        - name: A_B
          value: 0x01'01'00'00
        - name: A_C
          value: 0x01'02'00'00
        - name: B
          value: 0x02'00'00'00
          description: "State B description"
        - name: B_A
          value: 0x02'01'00'00
          description: "State B_A description"
        - name: B_B
          value: 0x02'02'00'00
          description: "State B_B description"
    """
    state_pairs: List[Dict[str, str]] = (
        []
    )  # the "value" of the second is in either 0bxxxxx or 0x..... format

    assert len(states) < 255, "The number of top level states can not exceed 254"
    for idx0, s0 in enumerate(states):
        ord0 = idx0 + 1
        # top level state
        state_pairs.append(
            {
                "name": s0["name"],
                "value": f"0x{ord0:02x}'00'00'00",
                "description": f"{s0['description']}",
            }
        )
        if "states" in s0:
            assert (
                len(s0["states"]) < 255
            ), "The number of second level states can not exceed 254"
            for idx1, s1 in enumerate(s0["states"]):
                ord1 = idx1 + 1
                # 2nd tier
                state_pairs.append(
                    {
                        "name": s0["name"] + "_" + s1["name"],
                        "value": f"0x{ord0:02x}'{ord1:02x}'00'00",
                        "description": f"{s1['description']}",
                    }
                )
                if "states" in s1:
                    assert (
                        len(s1["states"]) < 255
                    ), "The number of third level states can not exceed 254"
                    for idx2, s2 in enumerate(s1["states"]):
                        ord2 = idx2 + 1
                        # 3rd tier
                        state_pairs.append(
                            {
                                "name": f"{s0['name']}_{s1['name']}_{s2['name']}",
                                "value": f"0x{ord0:02x}'{ord1:02x}'{ord2:02x}'00",
                                "description": f"{s2['description']}",
                            }
                        )
                        if "states" in s2:
                            assert (
                                len(s2["states"]) < 255
                            ), "The number of fourth level states can not exceed 254"
                            for idx3, s3 in enumerate(s2["states"]):
                                ord3 = idx3 + 1
                                # 4th tier
                                state_pairs.append(
                                    {
                                        "name": f"{s0['name']}_{s1['name']}_{s2['name']}_{s3['name']}",
                                        "value": f"0x{ord0:02x}'{ord1:02x}'{ord2:02x}'{ord3:02x}",
                                        "description": f"{s3['description']}",
                                    }
                                )
    return state_pairs


def bitset(n: str) -> str:
    """Converts a number (n) to a 2^(n-1) binary number string."""
    return f"0b{(1 << (int(n) - 1)):b}"


def replace_bools(some: Any) -> str:
    """Replaces True and False with true and false"""
    if isinstance(some, str):
        return some.replace("True", "true").replace("False", "false")
    if isinstance(some, bool):
        return str(some).lower()
    return str(some)


def remove_void(param_string: str) -> str:
    """Removes 'void' from the parameter string."""
    return param_string.replace("void", "").strip()


def on_action(string: str, nl: str, var: Any) -> str:
    """Callback function for handling actions."""
    result: str = string
    if var is not None:
        # if var is a string which is "None"
        if isinstance(var, str):
            if var == "None":
                result += "" + nl
            elif var == "always":
                result = "always"
            elif var == "true" or var == "True":
                result = "true"
        elif isinstance(var, dict):
            # if var is a dictionary
            if "input" in var:
                result += f"triggered {var['input']}" + nl
            if "output" in var:
                result += f"raise {var['output']}" + nl
            if "expression" in var:
                result += f"{var['expression']}" + nl
            if "condition" in var:
                result += f"{var['condition']}" + nl
            if "interface" in var:
                result += f"call {var['interface']}()" + nl
    return result


class YamlLoader:
    """Loads the peripheral yaml files and keep track of what's been loaded."""

    def __init__(self, yaml_root: str) -> None:
        """A Yaml Loader which prevents loading the same file twice.

        Args:
            yaml_root (str): The root directory to look for yaml files.
        """
        self.yaml_root: str = yaml_root
        self.loaded_files: Dict[str, Dict[str, str]] = dict()

    def load(self, filename: str) -> typing.Optional[typing.Dict[str, str]]:
        """Loads a yaml file and returns the dictionary.
        Args:
            filename (str): The filename to load
        """
        if self.yaml_root is not None:
            filepath = os.path.join(self.yaml_root, filename)
        else:
            filepath = filename
        if filepath not in self.loaded_files:
            if verbose:
                print(f"Loading {filepath}")
            assert os.path.exists(
                filepath
            ), f"File {filepath} must exist (yaml_root={self.yaml_root})"
            with open(filepath, "r") as file:
                self.loaded_files[filepath] = yaml.load(
                    file.read(), Loader=yaml.SafeLoader
                )
        # raise Exception(f"Already loaded file {filepath}. There's probably a circular link.")
        return self.loaded_files[filepath]


def verify_keywords_statechart(data) -> None:
    """Verifies the statechart data."""
    required_keys = [
        "StateType",
        "EventType",
        "ClassName",
        "NameSpace",
        "states",
        "inputs",
        "outputs",
        "chart",
    ]
    for key in required_keys:
        assert key in data, f"Missing required key: {key}"
    for state in data["states"]:
        assert "name" in state, "Missing 'name' key in state"
    for inputs in data["inputs"]:
        assert "name" in inputs, "Missing 'name' key in input"
    for outputs in data["outputs"]:
        assert "name" in outputs, "Missing 'name' key in output"
    assert "entry" in data["chart"], "Missing 'entry' in chart"
    assert "exit" in data["chart"], "Missing 'exit' in chart"
    assert "states" in data["chart"], "Missing 'states' in chart"
    for state in data["chart"]["states"]:
        assert "in" in state, "Missing 'name' key in state"
        assert "transitions" in state, "Missing transitions in state"
        for transition in state["transitions"]:
            assert "trigger" in transition, "Missing Trigger in Transition"
            assert "guard" in transition, "Missing Guard in Transition"
            assert "target" in transition, "Missing Target in Transition"


def main(args: List[str]) -> int:
    global verbose
    parser = argparse.ArgumentParser(description="Staterator CLI")
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Enable verbose output"
    )
    parser.add_argument("-i", "--yaml-file", help="Path to the input file")
    parser.add_argument(
        "-r",
        "--yaml-root",
        default=os.getcwd(),
        help="Path to the root directory for yaml files",
    )
    parser.add_argument(
        "-t",
        "--template-file",
        action="append",
        help="Path to the template file default=%(default)s",
    )
    parser.add_argument(
        "-tr",
        "--template-root",
        default=os.path.join(os.getcwd(), "templates"),
        help="Path to the template root directory default=%(default)s",
    )
    parser.add_argument(
        "-g",
        "--generated",
        default="generated",
        help="Path to the output location default=%(default)s",
    )
    parser.add_argument(
        "-o", "--output", help="Base file name and extension for the output file"
    )
    parsed_args = parser.parse_args(args)

    input_file = parsed_args.yaml_file
    yaml_root = parsed_args.yaml_root
    template_root = parsed_args.template_root
    generated_dir = parsed_args.generated

    # Placeholder for actual processing logic
    print(f"Processing input file: {input_file}")
    print(f"Using template root: {template_root}")

    verbose = parsed_args.verbose or False  # in case it comes back None
    global loader  # declare globally
    loader = YamlLoader(yaml_root)

    # Takes the dictionary and emit through the templates
    env: Environment = Environment(loader=FileSystemLoader(template_root))
    env.globals["enum_states"] = enum_states
    env.filters["debug"] = lambda x: print(x) or x
    env.filters["list"] = list
    env.filters["conjoin"] = lambda ns: f"{ns}::"
    env.filters["on_action"] = on_action
    env.filters["remove_void"] = remove_void
    env.filters["replace_bools"] = replace_bools
    env.filters["bitset"] = bitset

    if input_file is not None:
        data = loader.load(input_file)
    else:
        data = {}

    # fill in defaults
    if "StateType" not in data:
        data["StateType"] = "std::uint32_t"
    if "EventType" not in data:
        data["EventType"] = "std::uint8_t"
    if "ClassName" not in data:
        data["ClassName"] = "FancyStateChart"
    if "NameSpace" not in data:
        data["NameSpace"] = "fancy"

    verify_keywords_statechart(data)

    for template_file in parsed_args.template_file:
        print(f"Using template file: {template_file}")
        template_name, template_ext, _ = template_file.split(".")

        # Alter the name of the output file
        output_file: str
        if parsed_args.output is None:
            output_name: str = template_name
            if template_name == "StateChart":
                output_name = str(data["ClassName"])
            if template_name == "gtest_statechart":
                output_name = "gtest_" + str(data["ClassName"])
            output_file = os.path.join(generated_dir, f"{output_name}.{template_ext}")
        else:
            output_file = os.path.join(generated_dir, parsed_args.output)
        print(f"Output will be saved to: {output_file}")

        # Create the output directory if it doesn't exist
        os.makedirs(os.path.dirname(output_file), exist_ok=True)

        # Write the rendered template to the output file
        with open(output_file, "w+") as file:
            template = env.get_template(template_file)
            file.write(template.render(data))

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
