/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Audio Input Redirection Virtual Channel
 *
 * Copyright 2010-2011 Vic Lee
 * Copyright 2015 Thincast Technologies GmbH
 * Copyright 2015 DI (FH) Martin Haimberger <martin.haimberger@thincast.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FREERDP_CHANNEL_CLIENT_AUDIN_H
#define FREERDP_CHANNEL_CLIENT_AUDIN_H

#include <freerdp/channels/audin.h>

/**
 * Subsystem Interface
 */

typedef WIN32ERROR (*AudinReceive) (BYTE* data, int size, void* userData);

typedef struct audin_format audinFormat;
struct audin_format
{
	UINT16 wFormatTag;
	UINT16 nChannels;
	UINT32 nSamplesPerSec;
	UINT16 nBlockAlign;
	UINT16 wBitsPerSample;
	UINT16 cbSize;
	BYTE* data;
};

typedef struct _IAudinDevice IAudinDevice;
struct _IAudinDevice
{
	WIN32ERROR (*Open) (IAudinDevice* devplugin, AudinReceive receive, void* userData);
	BOOL (*FormatSupported) (IAudinDevice* devplugin, audinFormat* format);
	WIN32ERROR (*SetFormat) (IAudinDevice* devplugin, audinFormat* format, UINT32 FramesPerPacket);
	WIN32ERROR (*Close) (IAudinDevice* devplugin);
	WIN32ERROR (*Free) (IAudinDevice* devplugin);
};

#define AUDIN_DEVICE_EXPORT_FUNC_NAME "freerdp_audin_client_subsystem_entry"

typedef WIN32ERROR (*PREGISTERAUDINDEVICE)(IWTSPlugin* plugin, IAudinDevice* device);

struct _FREERDP_AUDIN_DEVICE_ENTRY_POINTS
{
	IWTSPlugin* plugin;
	PREGISTERAUDINDEVICE pRegisterAudinDevice;
	ADDIN_ARGV* args;
};
typedef struct _FREERDP_AUDIN_DEVICE_ENTRY_POINTS FREERDP_AUDIN_DEVICE_ENTRY_POINTS;
typedef FREERDP_AUDIN_DEVICE_ENTRY_POINTS* PFREERDP_AUDIN_DEVICE_ENTRY_POINTS;

typedef WIN32ERROR (*PFREERDP_AUDIN_DEVICE_ENTRY)(PFREERDP_AUDIN_DEVICE_ENTRY_POINTS pEntryPoints);

#endif /* FREERDP_CHANNEL_CLIENT_AUDIN_H */

