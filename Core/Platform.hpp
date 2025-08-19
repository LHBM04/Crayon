#ifndef CR_ATTRIBUTES_H
#define CR_ATTRIBUTES_H

#if defined(_WIN32) || defined(_WIN64)
    #define NOMAD_PLATFORM_WINDOWS
    #define NOMAD_PLATFORM_DESKTOP
    #define NOMAD_PLATFORM_WINAPI
#elif
    #error "Unsupported platform not yet!"
#endif

#endif // !CR_ATTRIBUTES_H