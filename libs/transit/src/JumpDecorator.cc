JumpDecorator::JumpDecorator(IStrategy* strategy, double time,
  double jumpHeight)
  : ICelebrationDecorator(strategy, time), jumpHeight(jumpHeight) {}

void JumpDecorator::celebrate(IEntity* entity, double dt) {
  // Calculate the step for vertical movement based on entity speed and time
  Vector3 step(0, entity->getSpeed() * dt, 0);

  // Move the entity upwards if currently moving up
  if (up) {
    h += step.y; // Increment the current height
    entity->setPosition(entity->getPosition() + step); // Move entity up
    // Check if reached the target jump height
    if (h >= jumpHeight) up = false;
  } 
  // Move the entity downwards if currently moving down
  else {
    h -= step.y; // Decrement the current height
    entity->setPosition(entity->getPosition() - step); // Move entity down
    // Check if reached the ground level
    if (h <= 0) up = true;
  }
}
