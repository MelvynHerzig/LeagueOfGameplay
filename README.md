# League Of Gameplay
Project implementing some League of Legends gameplay in Unreal Engine 5 with Gameplay Ability System (GAS)


# Table of Contents

0. [Setup](#0-setup)
1. [Adding a character](#1-adding-a-character-with-movement)
1. [Camera movement](#2-camera-movement)


# 0) Setup

<details>

<summary>Expand</summary>

The project is setup based on an empty project with starter content. In preparation for the next steps, the cursor and mannequins from the Top Down starter project have also been imported. A `L_RiftPrototype` has been created as a workspace and set as the default editor map.

</details>

# 1) Adding a character with movement

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

# 2) Camera movement

<details>

<summary>Expand</summary>

In this chapter, I introduced camera movement functionality. In a typical MOBA game, there are usually three primary camera behaviors:

- <b>Edge Scrolling</b>: Moving the camera when the mouse is near the edges of the screen
- <b>Zooming</b>: Using the mouse wheel to zoom in and out
- <b>Camera Lock</b>: Locking the camera to follow the player's character

## 2.1) Decoupling the Camera from the Character

In the previous chapter, we setup `LgpCharacter` o that both the avatar and the camera were part of the same character blueprint. This tightly coupled setup made it difficult to move the camera freely.

To resolve this, I created a separate class called `LgpCamera`. It replicates the same top-down setup with a Spring Arm and Camera component, similar to what we had in `LgpCharacter`. A corresponding Blueprint, BP_LgpCamera, was also created.

Now, the `LgpPlayerController` is responsible for spawning the camera in the `OnPossess` function. After spawning, we set the view target to the new camera instance.


## 2.2) Camera movement

All camera movement logic is handled within the `LgpCamera` class. In the `Tick` function, we retrieve the mouse position and viewport size. By centering the origin in the middle of the screen, we can check if the mouse is outside the defined dead zone. If it is, we convert the offset into movement input (values of 1, -1, or 0), then multiply by the movement speed and delta time to update the camera position accordingly.

## 2.2) Camera zoom

A new input action, `IA_Zoom`, was created and bound to the mouse wheel in the `IMC_Controller` input mapping context. In `LgpController`, the action is handled by the `OnZoomTriggered` method, which is triggered on every scroll event.

This method calls `LgpCamera.Zoom`, which sets a target arm length. The `Tick` function then smoothly interpolates the spring arm's length toward this target value.



## 2.2) Camera lock

Another input action, `IA_LockCamera`, was added and bound to the spacebar in the `IMC_Controller`. In `LgpController`, this input is handled by:

- `OnLockCameraStarted`: Calls `LgpCamera.Follow`, which stores a reference to the target pawn. On each tick, if a pawn is set, the camera follows its position and disables manual movement. The pawn's movement component is configured to tick before the camera to prevent a one-frame delay.

- `OnLockCameraReleased`: Calls `LgpCamera.StopFollow`, which clears the pawn reference and restores normal camera control.

</details>