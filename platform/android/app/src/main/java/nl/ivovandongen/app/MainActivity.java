package nl.ivovandongen.app;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import nl.ivovandongen.lib.Native;

public class MainActivity extends AppCompatActivity {

  static {
    System.loadLibrary("native-lib");
  }

  private Handler handler;
  private Runnable task;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
  }

  @Override
  protected void onResume() {
    super.onResume();
    handler = new Handler(getMainLooper());
    task = new Runnable() {
      @Override
      public void run() {
        new Native().execute();
        handler.postDelayed(task, 2);
      }
    };

    handler.post(task);
  }

  @Override
  protected void onPause() {
    super.onPause();
    if (handler != null && task != null) {
      handler.removeCallbacks(task);
      handler = null;
    }
  }
}
