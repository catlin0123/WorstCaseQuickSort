//scrambles a list into the worst case for a median of three where the pivot 
//is swapped to the left. 
//n is size of list
//sorted is a sorted list of length n
//scrambled will store the worst case for a median of three
void scrambleList (int n, int[] sorted, int[] scrambled)
{
	//l is the power we are working on 
	//start in the starting index odd numbers 
	//step is the current step we are on
	int l = 0, start, step; 
	//place the odd numbers in
	for (int p = 1; p < n; )
	{
		start = pow (2, l) - 1; 
		step = pow(2, l+1); 
		while (start < (n-1)/2)
		{
			scrambled[start] = sorted[p]; 
			p = p + 2; 
			start = start + step; 
		}
		l++; 
	}
	
	//placing the even numbers in
	int num = 0; 
	for (int i = (n-1)/2; i < n - 1; i++)
	{
		scrambled[i] = sorted[num];
		num = num + 2; 
	}

	//placing the last number in 
	scrambled[n-1] = sorted[n-1];
}

//integer power function
int pow (int base, int power); 
{
	if (power == 0)
	{
		return 1; 
	}
	if (power % 2 == 1)
	{
		return pow(base, power-1) * x; 
	}
	int z = pow(base, power/2); 
	return z*z; 
}