package org.qtproject.example.TaskManager;

import android.content.Context;
import android.media.AudioManager;
import android.media.ToneGenerator;
import android.media.AudioAttributes;
import android.os.Build;

/**
 * Java helper class to play system sounds on Android
 * This class will be called from Qt C++ using JNI
 */
public class SoundHelper {
    
    /**
     * Play a simple beep sound when a task is created
     * @param context Android application context
     */
    public static void playTaskCreatedSound(Context context) {
        try {
            // Create ToneGenerator for system sounds
            // TONE_CDMA_ALERT_CALL_GUARD = 97 (a pleasant notification tone)
            ToneGenerator toneGenerator = new ToneGenerator(AudioManager.STREAM_NOTIFICATION, 100);
            toneGenerator.startTone(ToneGenerator.TONE_CDMA_ALERT_CALL_GUARD, 200); // 200ms duration
            
            // Clean up after a short delay
            new android.os.Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    toneGenerator.release();
                }
            }, 300);
            
        } catch (Exception e) {
            // Silently fail if sound cannot be played
            // This ensures the app doesn't crash if audio is unavailable
        }
    }
}
