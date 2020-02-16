/*
	TERNARY SEARCH: 
	-	search the optima of a unimodal function.
	
	Unimodal function: strictly increases then decreases or vice versa.
	=> f(i) = f(i+1) will never happen
*/

// finds maxima of f(x) in range [l, r] upto the  precision of eps.
double ternary_search_double(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)){
            l = m1;
        } else {
        	// f(m1) > f(m2)
            r = m2;
        }
    }
    return f(l);                 	// return the maximum of f(x) in [l, r]
}

// finds maxima of f(x) in {l, l+1, ..., r}
int ternary_search_int(int l, int r) {
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)){
            l = m1;
        } else {
        	// f(m1) > f(m2)
            r = m2;
        }
    }
    
    // linear search for maxima in [l, r]
    int imax = l;
    for(int i = l; i <= r; i++)
    	if(f(i) > f(imax)) 
    		imax = i;
    
    return f(imax);                 	// return the maximum of f(x) in [l, r]
}

// finds maxima of f(x) in {l, l+1, ..., r}
// better than previous method
int ternary_search_int_better(int l, int r) {
	while(l < r) {
		int mid = l + (r - l) / 2;
		if(f(mid) < f(mid + 1)) {
			l = mid + 1;
		} else {
			// f(mid) > f(mid + 1)
			r = mid;
		}
	}
	return f(l);
}
