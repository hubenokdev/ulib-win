//////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#define FILE_DEVICE_EVENT  0x8000
#define METHOD_BUFFERED    0

#define CTL_CODE(DeviceType, Function, Method, Access)( \
	((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))

// Define Interface reference/dereference routines for
// Interfaces exported by IRP_MN_QUERY_INTERFACE

#define FILE_ANY_ACCESS                   0x00000000

#define EVENT_IOCTL(index) \
    CTL_CODE(FILE_DEVICE_EVENT, index, METHOD_BUFFERED, FILE_READ_DATA)

#define IOCTL_PASSEVENT \
    CTL_CODE(FILE_DEVICE_EVENT, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PASSBUF \
    CTL_CODE(FILE_DEVICE_EVENT, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UNPASSEVENT \
    CTL_CODE(FILE_DEVICE_EVENT, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PASSEVSTRUCT \
    CTL_CODE(FILE_DEVICE_EVENT, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct        //这个结构主要用于调试用
{
    BOOL SHOWTHREAD;
    BOOL ONLYSHOWREMOTETHREAD;
    BOOL SHOWTERMINATEPROCESS;
    BOOL SHOWTERMINATETHREAD;
}CHECKLIST, *PCHECKLIST;


//////////////////////////////////////////////////////////////////////////////////////////
