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

## A* on a grid
A grid have been implemented using an XML file with the Grid Data, then a A* pathfing algorithm is apply to get the path. And finaly the path is send to the PathFollowing steering behavior.

## A* on a custom Nav Mesh
A nav mesh have been implemented using an XML file to load the Nav mesh Data, then a A* pathfing algorithm is apply to get the path. And finaly the path is send to the PathFollowing steering behavior.

## State machine
A state machine is implemented to create complex behavior.

## Custom Behavior tree
A custom behavior tree is implemented to create complex behavior.

