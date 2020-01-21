#ifndef __QUICK_SORT__
#define __QUICK_SORT__
void quick_sort(int* ar, int l, int r ){
	if(l>=r) return;
	int pivot=ar[(l+r)/2];
	int i=l, j=r;
	while(i<j){
		while(pivot>ar[i]&&i<=r) i++;
		while( pivot<ar[j]&& j>=l) j--;
		if(i>j) break;
		int t=ar[i]; 
		ar[i]=ar[j];
		ar[j]=t;
		i+=1;
		j-=1;
	}
	if(l<j) quick_sort( ar, l, j);
	if(i<r) quick_sort(ar, i, r);
	return;
}
#endif
