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

truthiness = ["true", "True", True, "on", "On", "ON", 1, "1"]
falsiness = ["false", "False", False, "off", "Off", "OFF", 0, "0"]


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
        - name: D
          states:
            - name: E
            - name: F
    out:
        - name: A
          value: 0x01'00'00'00
        - name: B
          value: 0x01'01'00'00
        - name: C
          value: 0x01'01'01'00
        - name: D
          value: 0x02'00'00'00
          description: "State D description"
        - name: E
          value: 0x02'01'00'00
          description: "State E description"
        - name: F
          value: 0x02'02'00'00
          description: "State F description"
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
                        "name": s1["name"],
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
                                "name": s2["name"],
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
                                        "name": s3["name"],
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


def on_interface_call(string: str, interface: dict, call: dict) -> str:
    """Finds the call in the interface and constructs the call string with parameters and return type if any.
    interface:
      - name: Foo
        return_type: void
        parameters: int a, float b
      - name: DoSomething
        return_type: int
        parameters: void

    call:
        name: DoSomething
        parameters: void
        assign: result
    """
    result: str = string
    for method in interface:
        if method["name"] == call["name"]:
            call_params: str = ""
            if "parameters" in method and method["parameters"] != "void":
                if "parameters" in call and call["parameters"] != "void":
                    call_params = call["parameters"]
            if "return_type" in method and method["return_type"] != "void":
                if "assign" in call and call["assign"] != "void":
                    result += f"{call['assign']} = "
                elif "expected" in call and call["expected"] is not None:
                    expected: str = call["expected"]
                    if expected in truthiness:
                        expected = "true"
                    elif expected in falsiness:
                        expected = "false"
                    result += f"{expected} == "
            result += f"callback_.{method['name']}({call_params})"
    return result


def final_filter(target: str) -> str:
    """If the target is Final, return [*], else return the target."""
    if target == "Final":
        return "[*]"
    return target


def dot_action(string: str, nl: str, var: Any) -> str:
    """Callback function for creating strings for diagramming actions."""
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
                result += f"triggered {var['input']}" + "/" + nl
            if "condition" in var:
                result += f"[{var['condition']}]" + nl
            if "output" in var:
                result += f"raise {var['output']}" + nl
            if "expression" in var:
                result += f"{var['expression']}" + nl
            if "call" in var:
                if "expected" in var["call"]:
                    expected: str = var["call"]["expected"]
                    if expected in truthiness:
                        result += f"[{var['call']['name']}()]" + nl
                    elif expected in falsiness:
                        result += f"[!{var['call']['name']}()]" + nl
                    else:
                        result += f"[{expected} = {var['call']['name']}()]" + nl
                else:
                    result += f"{var['call']['name']}()" + nl
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


def verify_action(
    action: Any,  # None, str, or Dict[str, str]
    interface: List[Dict[str, str]],
    outputs_list: List[Dict[str, str]],
) -> bool:
    """An Action is either/or/and an output, expression or interface call."""
    if action is None:
        return True
    if isinstance(action, str) and (action == "None" or action in truthiness):
        return True
    assert (
        "output" in action or "expression" in action or "call" in action
    ), "An Action must have either an output, expression or call"
    if "call" in action:
        verify_call(interface, action["call"], False)
    if "output" in action:
        outputs = [output["name"] for output in outputs_list]
        assert (
            action["output"] in outputs
        ), "The output must be defined in the outputs list"
    if "expression" in action:
        assert isinstance(action["expression"], str), "The expression must be a string"
    return True


def verify_stimulus(
    stimulus: Dict[str, str],
    inputs_list: List[Dict[str, str]],
    interface: List[Dict[str, str]],
) -> bool:
    """A stimulus is either an input, condition or a call which must resolve to a bool"""
    assert (
        "input" in stimulus or "condition" in stimulus or "call" in stimulus
    ), "A Stimulus must have either an input, condition or call"
    if "call" in stimulus:
        verify_call(interface, stimulus["call"], True)
    if "input" in stimulus:
        inputs = [input_def["name"] for input_def in inputs_list]
        assert (
            stimulus["input"] in inputs
        ), "The input must be defined in the inputs list"
    if "condition" in stimulus:
        assert isinstance(stimulus["condition"], str), "The condition must be a string"
    return True


def verify_call(interface: dict, call: dict, in_guard: bool) -> bool:
    """Verifies that the call exists in the interface."""
    for method in interface:
        assert "name" in method, "A method must have a name"
        assert "name" in call, "A method must have a name"
        if method["name"] == call["name"]:
            assert not (
                "assign" in call and "expected" in call
            ), "A call can not have both assign and expected"
            if not in_guard:
                return True
            else:
                # in a guard, the return type must be bool
                if "return_type" in method and method["return_type"] == "bool":
                    return True
    return False


def verify_state(
    state: dict,
    states_list: List[Dict[str, str]],
    inputs_list: List[Dict[str, str]],
    outputs_list: List[Dict[str, str]],
    interface_list: List[Dict[str, str]],
    level: int = 1,
) -> bool:
    """Verifies that the state exists in the list of states."""
    assert level < 5, "States can only be nested up to 4 levels deep"
    assert "in" in state, "A chart.state must have an 'in' key"
    # may have on_entry, on_exit, on_cycle
    if "on_entry" in state:
        verify_action(state["on_entry"], interface_list, outputs_list)
    if "on_exit" in state:
        verify_action(state["on_exit"], interface_list, outputs_list)
    if "on_cycle" in state:
        verify_action(state["on_cycle"], interface_list, outputs_list)
    assert len(states_list) > 0, "There must be at least one state defined"
    state_names = [s["name"] for s in states_list]
    assert (
        state["in"] in state_names
    ), f"State {state['in']} is not defined in the states names"
    if "states" in state:
        for substate in state["states"]:
            # find the substat list in the states list
            substates = list()
            for state_def in states_list:
                if state_def["name"] == state["in"]:
                    assert (
                        "states" in state_def
                    ), f"State {state_def['name']} has no substates"
                    substates = state_def["states"]

            verify_state(
                substate,
                substates,
                inputs_list,
                outputs_list,
                interface_list,
                level + 1,
            )
    # found the state in the state list but there's more
    assert "transitions" in state, "Missing transitions in state"
    for transition in state["transitions"]:
        assert (
            "trigger" in transition and transition["trigger"] is not None
        ), "Missing Trigger in Transition"
        assert (
            "guard" in transition and transition["guard"] is not None
        ), "Missing Guard in Transition"
        assert (
            "target" in transition and transition["target"] is not None
        ), "Missing Target in Transition"

        if isinstance(transition["trigger"], dict):
            assert "input" in transition["trigger"], "Missing Input in Trigger"
            # assert that the input is in the inputs list
            assert transition["trigger"]["input"] in [
                input_def["name"] for input_def in inputs_list
            ], f"Input {transition['trigger']['input']} is not defined in the inputs list"
        elif isinstance(transition["trigger"], str):
            assert (
                transition["trigger"] == "always" or transition["trigger"] == "true"
            ), "Trigger must be either 'always', 'true' or have an input"
        else:
            raise Exception(
                "Trigger must be either a string (always or true) or a dictionary"
            )

        # a guard can be "true", None or a condition, or a call
        if isinstance(transition["guard"], dict):
            assert (
                "condition" in transition["guard"] or "call" in transition["guard"]
            ), "Missing Condition or Call in Guard"  # Guards can ONLY have conditions or Calls (with bool return type)
            if "call" in transition["guard"]:
                assert verify_call(
                    interface_list, transition["guard"]["call"], True
                ), f"Call {transition['guard']['call']['name']} in guard is not defined in the interface or does not return bool"
        else:
            assert (
                transition["guard"] == "true" or transition["guard"] == "None"
            ), "Guard must be either 'None', 'true' (same as None) or have a condition"

        # it may also have a block which must have either an output, or expression or interface
        if "block" in transition:
            block: Dict = transition["block"]
            assert (
                "output" in block or "expression" in block or "call" in block
            ), "Block must have either an output, expression or call"

    return False


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
        # "includes", `# optional`
    ]
    for key in required_keys:
        assert key in data, f"Missing required key: {key}"
    for state in data["states"]:
        assert "name" in state, "Missing 'name' key in state"
    for inputs in data["inputs"]:
        assert "name" in inputs, "Missing 'name' key in input"
    for outputs in data["outputs"]:
        assert "name" in outputs, "Missing 'name' key in output"
    for method in data["interface"]:
        assert "name" in method, "Missing 'name' key in method"
        assert "description" in method, "Missing 'description' key in method"
        assert "params" in method, "Missing 'params' key in method"
        assert "modifiers" in method, "Missing 'modifiers' key in method"
        assert "return_type" in method, "Missing 'return_type' key in method"
    if "includes" in data:
        for header in data["includes"]:
            assert (
                header.endswith(".hpp")
                or header.endswith(".h")
                or header.startswith("<")
            ), f"Include {header} should be a .hpp, .h or system header"
    assert (
        "entry" in data["chart"]
    ), "Missing 'entry' in chart, must have an entry state"
    # [Optional]
    # assert "enter" in data["chart"], "Missing 'enter' in chart"
    # assert "exit" in data["chart"], "Missing 'exit' in chart"
    assert "states" in data["chart"], "Missing 'states' in chart"
    for state in data["chart"]["states"]:
        verify_state(
            state, data["states"], data["inputs"], data["outputs"], data["interface"]
        )


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
    env.filters["dot_action"] = dot_action
    env.filters["on_interface_call"] = on_interface_call
    env.filters["remove_void"] = remove_void
    env.filters["replace_bools"] = replace_bools
    env.filters["bitset"] = bitset
    env.filters["final_filter"] = final_filter

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
