/*
 * MM
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <raylib.h>
#include <physfs.h>
#include <mullemaus/core/filesystem.hpp>
#include <mullemaus/core/log.hpp>
//#include <mullemaus/core/mullemaus.hpp>
#include <globalConfig.hpp>

bool MM::Filesystem::isReady = false;

bool MM::Filesystem::Init() {
    if (isReady)
      return true;
    if (PHYSFS_init(nullptr) == 0){
      LOG_FATAL("Kann Virtuelles Dateisystem nicht laden: {}",PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    const char *perfDir = PHYSFS_getPrefDir("Mullemaus", /*MM::Mullemaus::Instance()->GetAppName().c_str()*/"fixme");
    if (perfDir == nullptr)
      return false;
    PHYSFS_setWriteDir(perfDir);
    isReady = true;
    LOG_INFO ("Virtuelles Dateisystem geladen");
    return true;
}

bool MM::Filesystem::Close() {
    if (PHYSFS_deinit() == 0){
      LOG_ERROR("Kann Virtuelles Dateisystem nicht schließen: {}",     PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    LOG_INFO ("Virtuelles Dateisystem geschloßen");
    return true;
}

bool MM::Filesystem::Mount(const std::string &dev, const std::string &mountPoint) {
    if (PHYSFS_mount(dev.c_str(), mountPoint.c_str(), 1) == 0){
      LOG_ERROR ("Kann {} nicht auf {} einbinden: {}", dev, mountPoint, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    LOG_INFO ("{} auf {} eingehängen", dev, mountPoint);
    return true;
}

bool MM::Filesystem::Unmount(const std::string &mountPoint) {
    if (PHYSFS_unmount(mountPoint.c_str()) == 0){
      LOG_ERROR("Kann {} nicht aushängen: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    LOG_INFO ("{} ausgehangen", mountPoint);
    return true;
}

bool MM::Filesystem::FileExists(const std::string &filename) {
    PHYSFS_Stat stat;
    if (PHYSFS_stat(filename.c_str(), &stat) == 0){
      LOG_ERROR ("{} nicht gefunden", filename);
      return false;
    }
    return stat.filetype == PHYSFS_FILETYPE_REGULAR;
}

bool MM::Filesystem::DirectoryExists(const std::string &path) {
    PHYSFS_Stat stat;
    if (PHYSFS_stat(path.c_str(), &stat) == 0){
      LOG_ERROR ("Verzeichnis {} nicht gefunden", path);
      return false;
    }
    return stat.filetype == PHYSFS_FILETYPE_DIRECTORY;
}

unsigned char *MM::Filesystem::LoadFileData(const std::string &filename, unsigned int *bytesRead) {
    *bytesRead = 0;
    if (FileExists(filename)){
      return nullptr;
    }
    
    auto *handle = PHYSFS_openRead(filename.c_str());
    if (handle == nullptr){
      LOG_ERROR("Fehler beim lesen von {}: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return nullptr;
    }
    
    long int size = PHYSFS_fileLength(handle);
    if (size == -1){
      PHYSFS_close(handle);
      LOG_ERROR ("Kann größe von {} nicht ermitteln: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return nullptr;
    }
    
    if (size == 0){
      PHYSFS_close(handle);
      LOG_ERROR ("Datei {} ist leer", filename);
      return nullptr;
    }
    
    void *buffer = MemAlloc(size);
    long int read = PHYSFS_readBytes(handle, buffer, size);
    if (read < 0){
      MemFree(buffer);
      PHYSFS_close(handle);
      LOG_ERROR("Fehler beim lesen von {}: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return nullptr;
    }
    
    PHYSFS_close(handle);
    *bytesRead = read;
    return (unsigned char *)buffer;
}

std::string MM::Filesystem::LoadFileText(const std::string &filename) {
    unsigned int bytesRead;
    std::string ret;
    ret = (char *)LoadFileData(filename, &bytesRead);
    return ret;
}

bool MM::Filesystem::SetWriteDir(const std::string &dirPath) {
    if (PHYSFS_setWriteDir(dirPath.c_str()) == 0){
      LOG_ERROR ("Kann Arbeitsverzeichniss nicht setzen: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    return true;
}

bool MM::Filesystem::SaveFileData(const std::string &filename, const void *data, unsigned int bytesToWrite) {
    if (bytesToWrite == 0 || data == nullptr){
      LOG_WARN ("Es wird versucht 0 bytes in {} zu schreiben", filename);
      return true;
    }
    
    auto *handle = PHYSFS_openWrite(filename.c_str());
    if (handle == nullptr){
      LOG_ERROR("Konnte {} nicht öffnen: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    
    if (PHYSFS_writeBytes(handle, data, bytesToWrite) < 0){
      PHYSFS_close(handle);
      LOG_ERROR("Fehler beim schreiben in {}: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
      return false;
    }
    
    PHYSFS_close(handle);
    return true;
}

bool MM::Filesystem::SaveFileText(const std::string &filename, std::string &text) {
    const char *str = text.c_str();
    return SaveFileData(filename, str, TextLength(text.c_str()));
}

MM::Directory MM::Filesystem::LoadDirectory(const std::string &path) {
  Directory returnDir;
  returnDir.count = 0;
  returnDir.entries = nullptr;
  if (!DirectoryExists(path)){
     return returnDir;
  }
  
  returnDir.entries = PHYSFS_enumerateFiles(path.c_str());
  
  for (char **i = returnDir.entries; *i != nullptr; i++) {
    returnDir.count++;
  }
  return returnDir;
}
/*
MM::Texture2D *MM::Filesystem::LoadTexture(const char *filename) {
    ::Texture2D tex = LoadTextureFromPhysFS(filename);
    Texture2D *texturePointer = new Texture2D((void *) &tex);
    return texturePointer;
}

void *MM::Filesystem::LoadMusic(const char *filename) {
    return nullptr;//(void*) LoadMusicStreamFromPhysFS(filename);
}

void *MM::Filesystem::LoadEffect(const char *filename) {
    return nullptr;//(void*) LoadWaveFromPhysFS(filename);
}

MM::Font *MM::Filesystem::LoadFont(const char *filename, int size) {
    ::Font raylibFont = LoadFontFromPhysFS(filename, size, nullptr, 0);
    MM::Font *newFont = new MM::Font ((void*)&raylibFont, size);
    return newFont;
}

const char *MM::Filesystem::GetAppPerfDirectory(const char *organization, const char *application) {
    return GetPerfDirectory(organization, application);
}

const char *MM::Filesystem::GetMullemausPerfDirectory() {
    return GetPerfDirectory("Mullemaus", "Mullemaus");
}*/
