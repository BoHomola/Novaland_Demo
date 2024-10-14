////////////////////////////////////////////////////////////////////////////////
// File:        RigidbodyC.cpp
// Author:      Bohumil Homola
// Date:        10/14/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "Export.h"
#include "Physics/Rigidbody.h"

EXPORT Novaland::Physics::Transform GetTransform(Novaland::Physics::Rigidbody *rigidbody)
{
    return rigidbody->GetTransform();
}

EXPORT Novaland::Physics::Velocity GetVelocity(Novaland::Physics::Rigidbody *rigidbody)
{
    return rigidbody->GetVelocity();
}
