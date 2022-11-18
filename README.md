# FightingGameProjectUE5
A personal project to make a C++ heavy action fighting game in UE5. Features a custom player class with custom movement, finite statemachine logic, input buffering and animations

-My goal for this project was to do a more custom approach by making more custom system design in Unreal Engine, overriding only from APawn to get more control over things like movement mechanics and input, while also enjoying a far less bloated class to work from, which is what you'd get from overriding from ACharacter.

-The interesting classes start with "FG_" (fighting game for short). There's an abstract FG_BaseCharacter with the custom movement, statemachine logic and input-buffer which you override from for things like controllable player characters or enemies (so you can theoretically play as an enemy), which we can see with GasmaskGuy being the example.
This provides a layer of abstraction for when you want to make new characters, much like how unreals own ACharacter is structured.

-The finite statemachine behavior works in tandem with the input buffer, as whenever you enter a new state, it will check if you've inputted something since a short duration of time, and then try to perform that input, if possible. 
This behavior exists on the FG_BaseCharacter itself which means that if a player were to pilot an enemy that inherits from this class, you'll still have the input-buffer system

-The custom movement component called FG_CharacterMovementComponent comes with custom collision done by sweeping, a velocity-based movement model with friction, acceleration, rotation, max-speed, etc, and smooth stair-stepping/object clearance.

-The animations is done entirely through an animation blueprint which reads values from FG_gasmaskguy and listens to events to play montages. The animator blueprint has walking, jumping, additive-landing animations, Inverse Kinematics for the legs and additive blendspaces for leaning the character spine when accelerating or turning


