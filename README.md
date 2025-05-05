# League Of Gameplay
Project implementing some League of Legends gameplay in Unreal Engine 5 with Gameplay Ability System (GAS)


# Table of Contents

0. [Setup](#0-setup)
1. [Adding a character](#1-adding-a-character)


# 0) Setup

<details>

<summary>Expand</summary>

The project is setup based on an empty project with starter content. In preparation for the next steps, the cursor and mannequins from the Top Down starter project have also been imported. A `L_RiftPrototype` has been created as a workspace and set as the default editor map.

</details>

# 1) Adding a character

<details>

<summary>Expand</summary>

## 1.1) Spawn a character

To start working on gameplay, I first need a character. 

I began by creating a C++ class that will serve as the base class of our characters `LgpCharacter`.

> The prefix `Lgp` stands for "League of Gameplay".`

At this stage, this class includes a very basic setup:
- A camera and a spring arm component configured for a simple top-down view.
- Basic configuration of the movement component.
- Capsule component setup to overlap the mesh that will be used.

From this class, I created the Blueprint counterpart: `BP_LgpCharacter`. At that point, I simply configured `SKM_Manny` as the mesh and set the animation mode to use `ABP_Manny_C`.

To spawn the character in the world, we need a game mode. So, I created `LgpGameMode` and its Blueprint counterpart `BP_LgpGameMode`, where I set `BP_LgpCharacter` as default pawn class.

## 1.2) Adding movement

To make the character move, I need to set up some inputs. 

First, I created an input action `IA_MoveTo`, and then a mapping `IMC_Default`, where the input action is mapped to the right mouse button.

To handle movement, a player controller is needed `LgpPlayerController`. Most of the logic is done inside `SetupInputComponent` methode, where the previous input action is bound to callback methods:

- `OnMoveToStarted`
- `OnMoveToTriggered`
- `OnMoveToReleased`

These methods handle the navigation and spawn the cursor FX.

To wrap up this section, the last step is to assign the custom controller in the game mode.

</details>