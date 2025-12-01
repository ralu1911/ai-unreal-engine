# AI in Unreal Engine
## Resume
This is an Unreal Engine 5 AI project with this content:
- Steering behavior
- A* on a grid
- A* on a custom nav mesh
- State Machine
- Custom behavior tree

## Steering behavior

### Simple Steering behavior
The simple steering behavior are composed of varius movements:
- Seek, and arrive to move to the next point.
- Align to make the characrer look to the objetive.
- Avoid to move around obtacles.

### Complex steering behavior
The complex steering behavior are two:
- AlignToMovement, that combines Seek, arrive and Align to have a character that move and face the destination.
- PathFollowing, this behavior uses Aling to movement an a path struck to move to a point.
