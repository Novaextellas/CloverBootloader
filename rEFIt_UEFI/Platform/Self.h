/*
 * Self.h
 *
 *  Created on: Sep 28, 2020
 *      Author: jief
 */

#ifndef PLATFORM_SELF_H_
#define PLATFORM_SELF_H_

#include "../cpp_foundation/XString.h"
extern "C" {
#include <Uefi/UefiSpec.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePath.h>
#include <Protocol/SimpleFileSystem.h>
}

class Self
{
protected:
  EFI_HANDLE        m_SelfImageHandle;  // this efi.
  EFI_LOADED_IMAGE* m_SelfLoadedImage; // this efi.
  EFI_DEVICE_PATH*  m_SelfDevicePath; // path to device containing this efi.
  XStringW          m_SelfDevicePathAsXStringW; // path to device containing this efi.

  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *m_SelfSimpleVolume;  // Volume containing this efi.
  EFI_FILE*         m_SelfVolumeRootDir;  // Root dir of the volume containing this efi.

  XStringW          m_efiFileName = L""_XSW;
  EFI_DEVICE_PATH*  m_CloverDirFullDevicePath; // full path, including device, of the folder containing this efi.
  EFI_FILE*         m_CloverDir;               // opened folder containing this efi
  XStringW          m_CloverDirFullPath; // full path of folder containing this efi.
//  XStringW          m_CloverDirPath; // dirname containing this efi (contains just the dir, not the device path)

//  bool      m_OemDirExists;
//  EFI_FILE *m_OemDir;

  bool      m_ThemesDirExists;
  EFI_FILE *m_ThemesDir;

  EFI_STATUS _openDir(const XStringW& path, bool* b, EFI_FILE** efiDir);
  EFI_STATUS _initialize();

public:
  Self () : m_SelfImageHandle(NULL), m_SelfLoadedImage(NULL), m_SelfDevicePath(NULL), m_SelfDevicePathAsXStringW(),
            m_SelfSimpleVolume(NULL), m_SelfVolumeRootDir(NULL),
            m_CloverDirFullDevicePath(NULL), m_CloverDir(NULL), m_CloverDirFullPath()/*, m_CloverDirPath()*/, m_ThemesDirExists(false), m_ThemesDir(0) {};
  Self(const Self&) = delete;
  Self& operator = (const Self&) = delete;

  ~Self () {};

  EFI_STATUS initialize(EFI_HANDLE ImageHandle);
  EFI_STATUS reInitialize();
  void closeHandle();

  bool isInitialized() const { return m_CloverDir != NULL; }
  void checkInitialized() const
  {
    if ( !isInitialized() ) {
      panic("Self in not initialized");
    }
  }

  EFI_HANDLE getSelfImageHandle() { checkInitialized(); return m_SelfImageHandle; }
  const EFI_LOADED_IMAGE& getSelfLoadedImage() { checkInitialized(); return *m_SelfLoadedImage; }
  EFI_HANDLE getSelfDeviceHandle() { checkInitialized(); return getSelfLoadedImage().DeviceHandle; }
  const EFI_DEVICE_PATH& getSelfDevicePath() { checkInitialized(); return *m_SelfDevicePath; }

  const EFI_SIMPLE_FILE_SYSTEM_PROTOCOL& getSelfSimpleVolume() { checkInitialized(); return *m_SelfSimpleVolume; }
  const EFI_FILE& getSelfVolumeRootDir() { checkInitialized(); return *m_SelfVolumeRootDir; }

  const XStringW& getCloverEfiFileName() { checkInitialized(); return m_efiFileName; }
  const EFI_DEVICE_PATH& getCloverDirFullDevicePath() { checkInitialized(); return *m_CloverDirFullDevicePath; }
  const EFI_FILE& getCloverDir() { checkInitialized(); return *m_CloverDir; }
  const XStringW& getCloverDirFullPath() { checkInitialized(); return m_CloverDirFullPath; }
//  const XStringW& getCloverDirPath() { checkInitialized(); return m_CloverDirPath; } // returns path containing this efi. Like \\EFI\\CLOVER

//  bool oemDirExists() { checkInitialized(); return m_OemDirExists; }
//  const EFI_FILE& getOemDir() { checkInitialized(); return *m_OemDir; } // Oem dir name under SelfDir. Like "OEM\\MyBoard"

  bool themesDirExists() { checkInitialized(); return m_ThemesDirExists; }
  const EFI_FILE& getThemesDir() { checkInitialized(); return *m_ThemesDir; }

};

extern Self self;

#endif /* PLATFORM_SELF_H_ */
