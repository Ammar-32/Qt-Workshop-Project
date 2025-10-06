#include "androidsound.h"
#include <QGuiApplication>
#include <QDebug>

// Android-specific includes
#ifdef Q_OS_ANDROID
#include <QJniObject>
#endif

AndroidSound::AndroidSound(QObject *parent)
    : QObject(parent)
{
    initializeAndroidContext();
}

void AndroidSound::initializeAndroidContext()
{
#ifdef Q_OS_ANDROID
    QGuiApplication *app = qobject_cast<QGuiApplication*>(QCoreApplication::instance());
    
    if (!app) {
        qDebug() << "AndroidSound: Not running in QGuiApplication context";
        return;
    }
    
    // android context
    auto *androidApp = app->nativeInterface<QNativeInterface::QAndroidApplication>();
    
    if (!androidApp) {
        qDebug() << "AndroidSound: Android application interface not available";
        return;
    }
    
    // Get the Android Context - this is the key to accessing Android APIs
    m_androidContext = androidApp->context();
    
    if (!m_androidContext.isValid()) {
        qDebug() << "AndroidSound: Failed to get Android Context";
        return;
    }
    
    qDebug() << "AndroidSound: Android Context initialized successfully";
#else
    qDebug() << "AndroidSound: Not running on Android platform - sound functionality disabled";
#endif
}

void AndroidSound::playTaskCreatedSound()
{
#ifdef Q_OS_ANDROID
    // Check if we have a valid Android Context
    if (!m_androidContext.isValid()) {
        qDebug() << "AndroidSound: Cannot play sound - no valid Android Context";
        return;
    }
    
    qDebug() << "AndroidSound: Playing task created sound...";
    
    // Call the Java static method using QJniObject
    // 
    // Method signature breakdown:
    // - "org/qtproject/example/TaskManager/SoundHelper" = full Java class path (use / not .)
    // - "playTaskCreatedSound" = Java method name
    // - "(Landroid/content/Context;)V" = JNI signature:
    //   - (Landroid/content/Context;) = takes one parameter: Android Context object
    //   - V = returns void
    // - m_androidContext.object<jobject>() = pass the Android Context as jobject
    //
    // Why we use QJniObject::callStaticMethod<void>:
    // - callStaticMethod = calls a static Java method (no object instance needed)
    // - <void> = template parameter indicates return type (void in this case)
    // - If method returned int, we'd use callStaticMethod<jint>
    // - If method returned boolean, we'd use callStaticMethod<jboolean>
    
    QJniObject::callStaticMethod<void>(
        "org/qtproject/example/TaskManager/SoundHelper",             // Java class path (shorter)
        "playTaskCreatedSound",                           // Java method name  
        "(Landroid/content/Context;)V",                   // JNI signature: (Context)void
        m_androidContext.object<jobject>()                // Pass Android Context
    );
    
    qDebug() << "AndroidSound: Sound method called successfully";
#else
    qDebug() << "AndroidSound: Sound functionality only available on Android platform";
#endif
}

/**
 * DEMO: How to call different types of Java methods
 * 
 * // Call a method that returns an int:
 * jint result = QJniObject::callStaticMethod<jint>(
 *     "com/example/MyClass",
 *     "getNumber",
 *     "()I",  // no parameters, returns int
 * );
 * 
 * // Call a method that takes a String and returns boolean:
 * jboolean success = QJniObject::callStaticMethod<jboolean>(
 *     "com/example/MyClass", 
 *     "isValid",
 *     "(Ljava/lang/String;)Z",  // takes String, returns boolean
 *     QJniObject::fromString("test").object<jstring>()
 * );
 * 
 * // Call a method that takes int and String, returns void:
 * QJniObject::callStaticMethod<void>(
 *     "com/example/MyClass",
 *     "doSomething", 
 *     "(ILjava/lang/String;)V",  // takes int and String, returns void
 *     42,
 *     QJniObject::fromString("hello").object<jstring>()
 * );
 */
