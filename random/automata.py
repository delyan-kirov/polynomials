# %% Imports
from dataclasses import dataclass
from enum import Enum
from typing import List
import random

# %% States

class Floor(Enum):
    One = 1
    Two = 2
    Three = 3 
    Four = 4 
    Five = 5
    Six = 6
    Seven = 7

@dataclass 
class Idle:
    floor: Floor


@dataclass 
class MoveUp:
    floor: Floor


@dataclass 
class MoveDown:
    floor: Floor

State = Idle | MoveUp | MoveDown

@dataclass 
class Input:
    direction: State

class Elevator:

    curr_state: State
    todo_states: List[Input]

    def __init__(self) -> None:
        print("Initializing state")
        self.curr_state = Idle(Floor.One)
        self.todo_states = []
        pass

    def transition(self) -> None:
        new_state = self.todo_states[len(self.todo_states) - 1]
        print("")
        print("Transitioning to: ", new_state)
        self.todo_states.pop()
        self.curr_state = new_state.direction
        print("Finished at: ", self.curr_state)
        if len(self.todo_states) == 0:
            print("Finished execution")
            self.curr_state = Idle(self.curr_state.floor)

    def __str__(self) -> str:
        todo_states_str = "\n".join([str(state.direction) for state in self.todo_states])
        return f"Current State: {self.curr_state}\nTodo States:\n{todo_states_str}"


if __name__ == "__main__":
    # Create an instance of the Elevator class
    elevator = Elevator()

    # Generate random todo states for testing
    num_states = 5 * (10 ** 2)
    for _ in range(num_states):
        # Generate a random floor and direction for the todo state
        floor = random.choice(list(Floor))
        direction = random.choice([MoveUp(floor), MoveDown(floor)])
        elevator.todo_states.append(Input(direction))

    # Print the current state and todo states
    print("Initial state:")
    print(elevator)

    # Perform state transitions and print the updated state after each transition
    while elevator.todo_states:
        elevator.transition()
        print("After transition:")
        print(elevator)

