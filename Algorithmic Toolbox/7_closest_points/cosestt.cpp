#include <bits/stdc++.h>

using namespace std;

bool comparex(pair<double, double> &p1, pair<double, double> &p2)
{
  return (p1.first!=p2.first)? p1.first<p2.first : p1.second<p2.second;
}

bool comparey(pair<double, double> &p1, pair<double, double> &p2)
{
  return (p1.second!=p2.second)? p1.second<p2.second : p1.first<p2.first;
}


double cal_dis(pair<double, double> p1, pair<double, double> p2)
{
  return sqrt(pow(p1.first-p2.first,2)+pow(p1.second-p2.second,2));
}


// Function to generate a random test case with n points
vector<pair<double, double>> generateTestCase(int n) {
    // Use a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(-1000, 1000);

    vector<pair<double, double>> points;
    for (int i = 0; i < n; i++) {
        double x = dis(gen);
        double y = dis(gen);
        points.push_back({x, y});
    }
    return points;
}


// void stressTest() {
//     // Generate a random test case with a large number of points
//     int n = 10000;
//     <pair<double, double>> points = generateTestCase(n);

//     // Start the timer
//     auto start = chrono::high_resolution_clock::now();

//     // Call your closest points function here
//     // double result = minimal_distance(...);

//     // Stop the timer
//     auto end = chrono::high_resolution_clock::now();

//     // Calculate the elapsed time
//     double elapsedTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

//     // Print the result and elapsed time
//     cout << "Result: " << result << endl;
//     cout << "Elapsed Time: " << elapsedTime << " milliseconds" << endl;
// }

double dist(pair<double, double> p1, pair<double, double> p2)
{
	return sqrt( (p1.first - p2.first)*(p1.first - p2.first) +
				(p1.second - p2.second)*(p1.second - p2.second)
			);
}

double bruteForce(pair<double, double> P[], int n)
{
	double min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
}


double stripClosest(pair<double, double> strip[], int size, double d)
{
	double min = d; // Initialize the minimum distance as d

	// Pick all points one by one and try the next points till the difference
	// between y coordinates is smaller than d.
	// This is a proven fact that this loop runs at most 6 times
	for (int i = 0; i < size; ++i)
		for (int j = i+1; j < size && (strip[j].second - strip[i].second) < min; ++j)
			if (dist(strip[i],strip[j]) < min)
				min = dist(strip[i], strip[j]);

	return min;
}

double closestUtil(pair<double, double> Px[], pair<double, double> Py[], int n)
{
	// If there are 2 or 3 points, then use brute force
	if (n <= 3)
		return bruteForce(Px, n);

	// Find the middle point
	int mid = n/2;
	pair<double, double> midPoint = Px[mid];


	// Divide points in y sorted array around the vertical line.
	// Assumption: All x coordinates are distinct.
	pair<double, double> Pyl[mid]; // y sorted points on left of vertical line
	pair<double, double> Pyr[n-mid]; // y sorted points on right of vertical line
	int li = 0, ri = 0; // indexes of left and right subarrays
	for (int i = 0; i < n; i++)
	{
	if ((Py[i].first < midPoint.first || (Py[i].first == midPoint.first && Py[i].second < midPoint.second)) && li<mid)
		Pyl[li++] = Py[i];
	else
		Pyr[ri++] = Py[i];
	}

	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and
	// dr on right side
	double dl = closestUtil(Px, Pyl, mid);
	double dr = closestUtil(Px + mid, Pyr, n-mid);

	// Find the smaller of two distances
	double d = min(dl, dr);

	// Build an array strip[] that contains points close (closer than d)
	// to the line passing through the middle point
	pair<double, double> strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(Py[i].first - midPoint.first) < d)
			strip[j] = Py[i], j++;

	// Find the closest points in strip. Return the minimum of d and closest
	// distance is strip[]
	return stripClosest(strip, j, d);
}


double minimal_distance(pair<double, double> pointsx[], pair<double, double> pointsy[], int n) {
  if(n==3) return min(cal_dis(pointsx[0], pointsx[1]), min(cal_dis(pointsx[0], pointsx[2]), cal_dis(pointsx[1], pointsx[2])));
  if(n==2) return cal_dis(pointsx[0], pointsx[1]);
  if(n==1) return FLT_MAX;
  int mid= n/2;

  pair<double, double> pointsyl[mid], pointsyr[n-mid];

  int l=0, r=0;
  for(int i=0; i<n; i++)
  {
    if(((pointsy[i].first < pointsx[mid].first)
     || ((pointsy[i].first) == (pointsx[mid].first) && (pointsy[i].second < pointsx[mid].second))) && l<mid)
    {
      pointsyl[l] = pointsy[i];
      l++;
    }
    else
    {
      pointsyr[r] = pointsy[i];
      r++;
    }
  }
  double d1 = minimal_distance(pointsx, pointsyl, mid);
  double d2 = minimal_distance(pointsx+mid, pointsyr, n-mid);
  double d = min(d1, d2);
  pair<double, double> strip[n];
  int size=0;
  for(int i=0; i<n; i++) if(abs((pointsy[i].first) - (pointsx[mid].first))<d) strip[size] = pointsy[i], size++;
  
  for(int i=0; i<size; i++)
  {
    for(int j=i+1; j<size && (strip[j].second - strip[i].second)<d; j++)
    {
        if(cal_dis(strip[i], strip[j])< d) d= cal_dis(strip[i], strip[j]);
    }
  }
  return d;
}

void test()
{
  for(int g=0; g<1000; g++)
  {int n = 10;
  vector<pair<double, double>> tmp = generateTestCase(n);
  pair<double, double> pointsx[n], pointsy[n];
  for (int i = 0; i < n; i++)
  {
    pointsx[i] = tmp[i];
    pointsy[i] = tmp[i];
  } 
  sort(pointsx, pointsx+n, comparex);
  sort(pointsy, pointsy+n, comparey);

  double b =  closestUtil(pointsx, pointsy, n);
  double c = minimal_distance(pointsx, pointsy, n);
  if(b!=c)
  {
    // cout<<"test case "<<i<<endl;
    // for (int k = 0; k < n; k++)
    // {
    //   cout<<a[k]<<" ";
    // }
    cout<<endl<<"source :"<<b<<endl;
    cout<<endl<<"delara :"<<c<<endl<<endl<<endl;
    
  }
// else cout<<g<<" checked"<<endl;
}

  }
int main() {
  int n;
  cin >> n;
  pair<double, double> pointsx[n], pointsy[n];
  for (size_t i = 0; i < n; i++) 
  {
    double x,y;
    cin >> x >> y;
    pointsx[i] = {x,y};
    pointsy[i] = {x,y};

  }
  sort(pointsx, pointsx+n, comparex);
  sort(pointsy, pointsy+n, comparey);
  cout << fixed;
  cout << setprecision(9) << closestUtil(pointsx, pointsy, n) << "\n";

  // test();
}
