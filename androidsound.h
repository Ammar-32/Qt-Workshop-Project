#ifndef ANDROIDSOUND_H
#define ANDROIDSOUND_H

#include <QObject>
#include <QGuiApplication>

// Android-specific includes - only available on Android platform
#ifdef Q_OS_ANDROID
#include <QJniObject>
#endif

/**
 * AndroidSound - JNI Demo Class
 * 
 * This class demonstrates how to call Java methods from Qt C++ using QJniObject
 * 
 * Key Learning Points:
 * 1. How to get Android Context from Qt application
 * 2. How to call static Java methods using JNI signatures
 * 3. Understanding JNI signature format: (parameters)return_type
 * 
 * JNI Signature Cheat Sheet:
 * - V = void
 * - I = int  
 * - Z = boolean
 * - J = long
 * - F = float
 * - D = double
 * - Ljava/lang/String; = Java String object
 * - Landroid/content/Context; = Android Context object
 * - Lpackage/Class; = Any Java class (note: use / not . in package names)
 * 
 * Example signatures:
 * - "()V" = no parameters, returns void
 * - "(I)V" = takes int parameter, returns void  
 * - "(Ljava/lang/String;)I" = takes String parameter, returns int
 * - "(Landroid/content/Context;)V" = takes Context parameter, returns void
 */

class AndroidSound : public QObject
{
    Q_OBJECT

public:
    explicit AndroidSound(QObject *parent = nullptr);
    
    /**
     * Play a sound when a task is created
     * This method calls the Java SoundHelper.playTaskCreatedSound() method
     */
    void playTaskCreatedSound();

private:
#ifdef Q_OS_ANDROID
    QJniObject m_androidContext;
#endif
    
    /**
     * Initialize the Android Context
     * This is required to call most Android APIs
     */
    void initializeAndroidContext();
};

#endif // ANDROIDSOUND_H
