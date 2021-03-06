/*
 * Copyright (c) 2005-2017, BearWare.dk
 * 
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Kirketoften 5
 * DK-8260 Viby J
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk 5 SDK owned by
 * BearWare.dk. All copyright statements may not be removed 
 * or altered from any source distribution. If you use this
 * software in a product, an acknowledgment in the product 
 * documentation is required.
 *
 */

#ifndef TTCONVERT_JNI_H
#define TTCONVERT_JNI_H

#if defined(WIN32)
#define NOMINMAX 1
#include <Windows.h>
#endif

#include <jni.h>
#include <TeamTalk.h>

#define ZERO_STRUCT(s) memset(&s, 0, sizeof(s))

#if defined(WIN32)
#define NEW_JSTRING(env, str) (env->NewString(reinterpret_cast<const jchar*>(str), wcslen(str)))
#define TT_STRCPY(dst, src) do { wcsncpy(dst, src, TT_STRLEN); dst[TT_STRLEN-1]; } while(0)
const jint* TO_JINT_ARRAY(const INT32* ttints, jint* jints, INT32 N);
#else
#define NEW_JSTRING(env, str) (env->NewStringUTF(str))
#define TT_STRCPY(dst, src) do { strncpy(dst, src, TT_STRLEN); dst[TT_STRLEN-1]; } while(0)
#define TO_JINT_ARRAY(ttint32, jints, N) (ttint32)
#endif

const INT32* TO_INT32_ARRAY(const jint* jints, INT32* ttints, jsize N);

#define THROW_NULLEX(env, param, ret)                       do {        \
    if(param == 0) {                                                    \
    jclass cls = (env)->FindClass("java/lang/NullPointerException");    \
    env->ThrowNew(cls, #param " is null");                              \
    return ret;                                                         \
    }                                                                   \
    } while(0)

class ttstr
{
    JNIEnv* env;
    jstring js;
    const TTCHAR* str;
    ttstr(const ttstr&);
    const ttstr& operator = (const ttstr&);

public:
    ttstr(JNIEnv* e, jstring s)
        : env(e)
        , js(s)
        {
#if defined(WIN32)
            if(s)
                str = reinterpret_cast<const TTCHAR*>(env->GetStringChars(s, 0));
            else str = L"";
#else
            if(s)
                str = env->GetStringUTFChars(s, 0);
            else str = "";
#endif
        }
    
    ~ttstr()
        {
#if defined(WIN32)
            if(js)
                env->ReleaseStringChars(js, reinterpret_cast<const jchar*>(str));
#else
            if(js)
                env->ReleaseStringUTFChars(js, str);
#endif
        }
    operator const TTCHAR*() { return str; }
};

enum JConvert
{
    N2J = 1,
    J2N = 2
};

jobject newObject(JNIEnv* env, jclass cls_obj);
jobject newSoundDevice(JNIEnv* env, const SoundDevice& dev);
jobject newVideoDevice(JNIEnv* env, VideoCaptureDevice& dev);
jobject newChannel(JNIEnv* env, const Channel* lpChannel);
jobject newUser(JNIEnv* env, const User* lpUser);
jobject newClientErrorMsg(JNIEnv* env, const ClientErrorMsg* lpClientErrorMsg);
jobject newUserAccount(JNIEnv* env, const UserAccount* lpUserAccount);
jobject newTextMessage(JNIEnv* env, const TextMessage* lpTextMessage);
jobject newRemoteFile(JNIEnv* env, const RemoteFile* lpRemoteFile);
jobject newServerProperties(JNIEnv* env, const ServerProperties* lpServerProperties);
void setChannel(JNIEnv* env, Channel& chan, jobject lpChannel, JConvert conv);
void setUser(JNIEnv* env, const User& user, jobject lpUser);
void setTTMessage(JNIEnv* env, TTMessage& msg, jobject pMsg);
void setIntPtr(JNIEnv* env, jobject intptr, jint value);
jint getIntPtr(JNIEnv* env, jobject intptr);
void setAudioCodec(JNIEnv* env, AudioCodec& codec, jobject lpAudioCodec, JConvert conv);
void setAudioConfig(JNIEnv* env, AudioConfig& audcfg, jobject lpAudioConfig, JConvert conv);
void setSpeexDSP(JNIEnv* env, SpeexDSP& spxdsp, jobject lpSpeexDSP, JConvert conv);
void setServerProperties(JNIEnv* env, ServerProperties& srvprop, jobject lpServerProperties, JConvert conv);
void setClientStatistics(JNIEnv* env, const ClientStatistics& stats, jobject lpStats);
void setTextMessage(JNIEnv* env, TextMessage& msg, jobject lpTextMessage, JConvert conv);
void setUserAccount(JNIEnv* env, UserAccount& account, jobject lpAccount, JConvert conv);
void setServerStatistics(JNIEnv* env, ServerStatistics& stats, jobject lpServerStatistics, JConvert conv);
void setRemoteFile(JNIEnv* env, RemoteFile& fileinfo, jobject lpRemoteFile, JConvert conv);
void setUserStatistics(JNIEnv* env, const UserStatistics& stats, jobject lpUserStatistics);
void setFileTransfer(JNIEnv* env, const FileTransfer& filetx, jobject lpFileTransfer);
void setBannedUser(JNIEnv* env, const BannedUser& banned, jobject lpBannedUser);
void setClientErrorMsg(JNIEnv* env, ClientErrorMsg& cemsg, jobject lpClientErrorMsg, JConvert conv);
void setDesktopInput(JNIEnv* env, DesktopInput& input, jobject lpDesktopInput, JConvert conv);
void setDesktopWindow(JNIEnv* env, DesktopWindow& deskwnd, jobject lpDesktopWindow, JConvert conv);
void setVideoFrame(JNIEnv* env, VideoFrame& vidframe, jobject lpVideoFrame);
void setAudioBlock(JNIEnv* env, AudioBlock& audblock, jobject lpAudioBlock);
void setMediaFileInfo(JNIEnv* env, MediaFileInfo& mfi, jobject lpMediaFileInfo);
void setAudioFormat(JNIEnv* env, const AudioFormat& fmt, jobject lpAudioFormat);
void setVideoFormat(JNIEnv* env, VideoFormat& fmt, jobject lpVideoFormat, JConvert conv);
void setVideoCodec(JNIEnv* env, VideoCodec& codec, jobject lpVideoCodec, JConvert conv);
void setWebMVP8Codec(JNIEnv* env, WebMVP8Codec& webm_vp8, jobject lpWebMVP8Codec, JConvert conv);
#endif
