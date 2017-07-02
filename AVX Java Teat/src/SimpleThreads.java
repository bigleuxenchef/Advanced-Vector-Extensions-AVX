
//-XX:+UseSuperWord
//-XX:+DisableExplicitGC
//-XX:+AggressiveOpts

public class SimpleThreads {
	static void normal_add(float a[], int N) {
		for (int i = 0; i < N / 2; ++i)
			a[i] = a[i] + a[N / 2 + i];
	}

	static void normal_add_d(double a[], int N) {
		for (int i = 0; i < N / 2; ++i)
			a[i] = a[i] + a[N / 2 + i];
	}

	static void normal_sub(float a[], int N) {
		for (int i = 0; i < N / 2; ++i)
			a[i] = a[i] - a[N / 2 + i];
	}

	static void normal_sub_d(double a[], int N) {
		for (int i = 0; i < N / 2; ++i)
			a[i] = a[i] - a[N / 2 + i];
	}

	static <T extends Number> void normal_subT(T a[], int N) {
		for (int i = 0; i < N / 2; ++i)
			if (a[0] instanceof Float) {
				// System.out.printf("Float\n");
				a[i] = (T) (Number) (a[i].floatValue() - a[N / 2 + i].floatValue());
			} else if (a[0] instanceof Double) {
				// System.out.printf("Double\n");
				a[i] = (T) (Number) (a[i].doubleValue() - a[N / 2 + i].doubleValue());
			}

	}

	static <T extends Number> void normal_addT(T a[], int N) {
		if (a[0] instanceof Float)
			for (int i = 0; i < N / 2; ++i)
				a[i] = (T) (Number) (a[i].floatValue() + a[N / 2 + i].floatValue());
		else if (a[0] instanceof Double)
			for (int i = 0; i < N / 2; ++i)
				a[i] = (T) (Number) (a[i].doubleValue() + a[N / 2 + i].doubleValue());

	}

	static <T extends Number> void normal_addT2(T a[], int N) {
		for (int i = 0; i < N / 2; ++i) {
			if (a[0] instanceof Float)

				a[i] = (T) (Number) (a[i].floatValue() + a[N / 2 + i].floatValue());
			else if (a[0] instanceof Double)
				a[i] = (T) (Number) (a[i].doubleValue() + a[N / 2 + i].doubleValue());
		}

	}

	private static class TestLoop implements Runnable {
		public void run() {
			int i = 0;
			int N = 51200000;
			float[] a = new float[N];
			Number[] b = new Number[N];

			System.out.printf("\n\n!!!Hello World OF Advanced Vector Extensions for : iteration : %d \n", N);

			for (int j = 1; j < 100; j++) {
				for (i = 0; i < N; ++i) {
					a[i] = (float) 3141592.653588 + i;
					b[i] = (double) 3141592.653588 + i;
				}

				long timeStart = System.currentTimeMillis();

				normal_add(a, N);

				long TimeDuration = System.currentTimeMillis() - timeStart;

				System.out.printf("\nJava/Inline Float      Results Iteration # %d duration %d millis resultd\n", i,
						TimeDuration);

				timeStart = System.currentTimeMillis();

				normal_subT(b, N);

				TimeDuration = System.currentTimeMillis() - timeStart;

				System.out.printf(
						"\nJava/Inline Double/Template       Results Iteration # %d duration %d millis resultd\n", i,
						TimeDuration);

			}
		}

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Thread t = new Thread(new TestLoop());

		t.start();
	}
}
