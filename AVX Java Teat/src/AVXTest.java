import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TestName;




public class AVXTest {
	static int N = 51200000;
    @Rule public TestName name = new TestName();
	
	@Rule
	public RunInThreadRule runInThread = new RunInThreadRule();
	
	
	
	@BeforeClass public static void initialize() {
		System.out.printf("\n\n!!!Hello World OF Advanced Vector Extensions for : iteration : %d \n", N);

	    }
		
	@Test
	@RunInThread
	public void test_normal_add() {
		int i;
		float[] a = new float[N];
		
		System.out.printf("\n%s => ",name.getMethodName());

			for (i = 0; i < N; ++i)
				{a[i] = (float) 3141592.653588 + i;
				}

			long timeStart = System.currentTimeMillis();

			SimpleThreads.normal_add(a, N);

			long TimeDuration = System.currentTimeMillis() - timeStart;

			System.out.printf("Java/Inline Float      Results Iteration # %d duration %d millis resultd\n",i,
					TimeDuration);
			
		
			
		}
	@Test
	@RunInThread
	public void test_normal_sub() {
		int i;
		float[] a = new float[N];

		System.out.printf("\n%s => ",name.getMethodName());


			for (i = 0; i < N; ++i)
				{a[i] = (float) 3141592.653588 + i;
				}

			long timeStart = System.currentTimeMillis();

			SimpleThreads.normal_sub(a, N);

			long TimeDuration = System.currentTimeMillis() - timeStart;

			System.out.printf("Java/Inline Float      Results Iteration # %d duration %d millis resultd\n", i,
					TimeDuration);
			
		
			
		}
	
	
	@Test
	@RunInThread
	public void test_normal_add_d() {
		int i;
		double[] a = new double[N];

		System.out.printf("\n%s => ",name.getMethodName());



			for (i = 0; i < N; ++i)
				{a[i] = (double) 3141592.653588 + i;
				}

			long timeStart = System.currentTimeMillis();

			SimpleThreads.normal_add_d(a, N);

			long TimeDuration = System.currentTimeMillis() - timeStart;

			System.out.printf("Java/Inline Double      Results Iteration # %d duration %d millis resultd\n", i,
					TimeDuration);
			
		
			
		}
	
	@Test
	@RunInThread
	public void test_normal_sub_d() {
		int i;
		double[] a = new double[N];

		System.out.printf("\n%s => ",name.getMethodName());


			for (i = 0; i < N; ++i)
				{a[i] = (double) 3141592.653588 + i;
				}

			long timeStart = System.currentTimeMillis();

			SimpleThreads.normal_sub_d(a, N);

			long TimeDuration = System.currentTimeMillis() - timeStart;

			System.out.printf("Java/Inline Double      Results Iteration # %d duration %d millis resultd\n", i,
					TimeDuration);
			
		
			
		}
	
	
	@Test
	@RunInThread
	public void test_normal_subT() {
		int i;
		Number[] b = new Number[N];

		System.out.printf("\n%s => ",name.getMethodName());


			for (i = 0; i < N; ++i)
				{b[i] = (double) 3141592.653588 + i;
				}

			long timeStart = System.currentTimeMillis();

			SimpleThreads.normal_subT(b, N);

			long TimeDuration = System.currentTimeMillis() - timeStart;

			System.out.printf("Java/Inline Double/Template       Results Iteration # %d duration %d millis resultd\n", i,
					TimeDuration);
			
		
			
		}
		
	}

