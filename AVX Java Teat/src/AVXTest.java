import static org.junit.Assert.*;

import org.junit.After;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestName;

// JM options
// -ea
//-XX:+UseSuperWord
// -XX:UseAVX=1
// -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:+LogCompilation
// -XX:+PrintGC
// -Xprof

//-XX:UseSSE=3
//-XX:+UseSuperWord

public class AVXTest {
	static int N = 51200000;
	static long TimeDuration;
	static int i=0;
	
	@Rule
	public TestName name = new TestName();

	@Rule
	public RunInThreadRule runInThread = new RunInThreadRule();

	@BeforeClass
	public static void initialize() {
		System.out.printf("\n\n!!!Hello World OF Advanced Vector Extensions for : iteration : %d \n", N);

	}
	
	@After
	public void aftermethod()
	{
		System.out.printf("\n%s => ", name.getMethodName());
		System.out.printf("Java/Inline %s      Results Iteration # %d duration %d millis result\n",name.getMethodName().matches(".*_d")? "Double":"Float", i,
				TimeDuration);

	}
	

	@Test
	//@RunInThread
	public void test_normal_add() {
		float[] a = new float[N];

		for (i = 0; i < N; ++i) {
			a[i] = (float) 3141592.653588 + i;
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_add(a, N);

		TimeDuration = System.currentTimeMillis() - timeStart;

	}

	@Test
	//@RunInThread
	public void test_normal_sub() {
		float[] a = new float[N];

		for (i = 0; i < N; ++i) {
			a[i] = (float) 3141592.653588 + i;
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_sub(a, N);

		TimeDuration = System.currentTimeMillis() - timeStart;

	}

	@Test
	//@RunInThread
	public void test_normal_add_d() {
		double[] a = new double[N];

		for (i = 0; i < N; ++i) {
			a[i] = (double) 3141592.653588 + i;
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_add_d(a, N);

		TimeDuration = System.currentTimeMillis() - timeStart;

	

	}

	@Test
	//@RunInThread
	public void test_normal_sub_d() {
		double[] a = new double[N];

		for (i = 0; i < N; ++i) {
			a[i] = (double) 3141592.653588 + i;
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_sub_d(a, N);

		TimeDuration = System.currentTimeMillis() - timeStart;

	}

	@Test
	@RunInThread
	public void test_normal_subT() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (float) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_subT(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
	
	@Test //(timeout=1000)
	@RunInThread
	public void test_normal_subT_d() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (double) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_subT(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
	
	
	@Test
	@RunInThread
	public void test_normal_addT() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (float) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_addT(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
	@Test
	@RunInThread
	public void test_normal_addT_d() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (double) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_addT(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
	
	
	

	@Test
	@RunInThread
	public void test_normal_addT2() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (float) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_addT2(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
	@Test
	@RunInThread
	public void test_normal_addT2_d() {
		Number[] b = new Number[N];

		for (i = 0; i < N; ++i) {
			b[i] = (double) (3141592.653588 + i);
		}

		long timeStart = System.currentTimeMillis();

		SimpleThreads.normal_addT2(b, N);

		TimeDuration = System.currentTimeMillis() - timeStart;


	}
}
