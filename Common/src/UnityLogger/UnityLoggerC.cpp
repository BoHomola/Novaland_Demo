////////////////////////////////////////////////////////////////////////////////
// File:        UnityLoggerC.cpp
// Author:      Bohumil Homola
// Date:        10/16/2023
// Description:
////////////////////////////////////////////////////////////////////////////////

#include "UnityLoggerC.h"

IUnityLog *unityLogPtr = nullptr;

extern "C"
{
    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces *unityInterfacesPtr)
    {
        unityLogPtr = unityInterfacesPtr->Get<IUnityLog>();
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload()
    {
        unityLogPtr = nullptr;
    }
}
