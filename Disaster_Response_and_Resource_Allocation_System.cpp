#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define inf 999999
#define max_loc 10
#define max_rsc 9
#define max_edges 100

struct location
{
    int id;
    string name;
};

struct resource
{
    string name;
    int weight;
    int value;
};

struct edge_item
{
    int src, dest, weight;
};
resource resources[max_rsc] =
{
    {"Rice Pack", 5, 10},
    {"Drinking Water", 3, 8},
    {"Medical Kit", 4, 12},
    {"Rescue Boat", 10, 20},
    {"Dry Food", 2, 6},
    {"Tarpaulin Sheet", 6, 9},
    {"Life Jacket", 3, 11},
    {"Emergency Light", 2, 7},
    {"First Aid Spray", 1, 5}
};
int tot_rsc = 9;

location locations[max_loc]
{
    {0, "Khulna Sadar"},
    {1, "Batiaghata"},
    {2, "Dumuria"},
    {3, "Paikgacha"},
    {4, "Koyra"},
    {5, "Dacope"},
    {6, "Rupsa"},
    {7, "Terokhada"}
};

int graph[max_loc][max_loc] =
{
    {0, 5, 3, -1, 0, 0, 2, 0},
    {5, 0, 4, 6, 0, 0, 0, 0},
    {3, 4, 0, 2, 0, 0, 0, 0},
    {-1, 6, 2, 0, 3, 0, 0, 0},
    {0, 0, 0, 3, 0, 2, 0, 0},
    {0, 0, 0, 0, 2, 0, 1, 0},
    {2, 0, 0, 0, 0, 1, 0, 4},
    {0, 0, 0, 0, 0, 0, 4, 0}
};
int tot_loc = 8;

void print_line()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "=";
    }
    cout << endl;
}
void print_hy()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void new_line()
{
    cout << endl;
}

// ekhane auto correct er jonno lcs er function gula :)

string text_lower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
    }
    return s;
}

int findLCS(string a, string b)
{
    int m = a.length();
    int n = b.length();
    int dp[300][300];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }
    return dp[m][n];
}

int find_match(string s)
{
    string low_input = text_lower(s);
    int best_indx = 0;
    int best_score = -1;
    for (int i = 0; i < tot_loc; i++)
    {
        string low_location = locations[i].name;
        int score = findLCS(low_input, low_location);
        if (score > best_score)
        {
            best_score = score;
            best_indx = i;
        }
    }
    return best_indx;
}

int get_location(string prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        for (int i = 0; i < tot_loc; i++)
        {
            if (text_lower(locations[i].name) == text_lower(input))
                return i;
        }

        int match = find_match(input);
        new_line();

        char c;
        while (true)
        {
            cout << "Did you mean \"" << locations[match].name << "\" ? (y/n): ";
            cin >> c;
            cin.ignore();
            if (c == 'y' || c == 'Y' || c == 'n' || c == 'N')
                break;
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }

        if (c == 'y' || c == 'Y')
            return match;

        new_line();
        cout << "Available Locations: " << endl;
        for (int i = 0; i < tot_loc; i++)
        {
            cout << "    [" << i << "] " << locations[i].name << endl;
        }

        int indx;
        while (true)
        {
            cout << "Enter number (0-" << tot_loc - 1 << "): ";
            if (cin >> indx)
            {
                cin.ignore();
                if (indx >= 0 && indx < tot_loc)
                    return indx;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Invalid index. Please try again." << endl;
        }
    }
}

// Location dekha jak ei part e

void view_location()
{
    new_line();
    print_line();
    cout << "\tAFFECTED LOCATIONS - KHULNA REGION" << endl;
    print_line();
    new_line();
    cout << "      ID        Location Name" << endl;
    print_hy();
    for (int i = 0; i < tot_loc; i++)
    {
        cout << "     [" << i << "]        " << locations[i].name << endl;
    }
    print_line();
}

void view_road()
{
    new_line();
    print_line();
    cout << "     ROAD NETWORK - KHULNA DISTRICT" << endl;
    ;
    print_line();
    new_line();
    cout << "[N.B] -1 = flooded / impassable" << endl;
    new_line();
    print_hy();
    for (int i = 0; i < tot_loc; i++)
    {
        for (int j = i + 1; j < tot_loc; j++)
        {
            if (graph[i][j] == 0)
                continue;
            cout << "  " << locations[i].name << " <--> " << locations[j].name;
            int current_len = locations[i].name.length() + locations[j].name.length() + 5;
            int target_width = 30;
            for (int k = 0; k < (target_width - current_len); k++)
            {
                cout << " ";
            }
            cout << " = ";
            if (graph[i][j] == -1 || graph[j][i] == -1)
                cout << "ROAD DAMAGED!!" << endl;
            else
                cout << graph[i][j] << " km" << endl;
        }
    }
    print_line();
}

// ekhn korbo merge sort ;0

void merging(resource arr[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    resource left[50], right[50];

    for (int i = 0; i < n1; i++)
        left[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[q + 1 + j];
    left[n1].value = -1 * inf;
    right[n2].value = -1 * inf;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (left[i].value >= right[j].value)
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
    }
}

void merge_sort(resource arr[], int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merging(arr, p, q, r);
    }
}

void view_rscby_priority()
{
    resource temp[max_rsc];
    for (int i = 0; i < tot_rsc; i++)
        temp[i] = resources[i];

    merge_sort(temp, 0, tot_rsc - 1);

    new_line();
    print_line();
    cout << "\tSUPPLY RESOURCES - SORTED BY IMPORTANCE" << endl;
    cout << "\t(Merge Sort | Highest Priority First)" << endl;
    print_line();
    cout << "   Rank   Resource Name           Weight    Priority" << endl;
    print_hy();

    for (int i = 0; i < tot_rsc; i++)
    {
        cout << "    " << (i + 1);
        if (i + 1 < 10)
            cout << "      ";
        else
            cout << "     ";
        cout << temp[i].name;

        int name_len = temp[i].name.length();
        for (int k = name_len; k < 24; k++)
        {
            cout << " ";
        }
        cout << temp[i].weight;
        if (temp[i].weight < 10)
            cout << "         ";
        else
            cout << "        ";
        cout << temp[i].value << "\n";
    }
    print_line();
}

// ekhn hobe quick sort er khela, eta use korbo kruskal algo te edge sort korte

int Partition(edge_item A[], int p, int r)
{
    int x = A[r].weight;
    int i = p - 1;

    for (int j = p; j <= r - 1; j++)
    {
        if (A[j].weight <= x)
        {
            i++;
            edge_item temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    edge_item temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

void QuickSort(edge_item A[], int p, int r)
{
    if (p < r)
    {
        int q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

// eibar dijkstra kora jak

int minKey(int distance[], bool visited[])
{
    int minimum = inf;
    int minIndex = -1;

    for (int i = 0; i < tot_loc; i++)
    {
        if (!visited[i] && distance[i] < minimum)
        {
            minimum = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void run_dijkstra(int source, int destination)
{
    int distance[max_loc];
    bool visited[max_loc];
    int parent[max_loc];

    for (int i = 0; i < tot_loc; i++)
    {
        distance[i] = inf;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int i = 0; i < tot_loc - 1; i++)
    {
        int u = minKey(distance, visited);
        if (u == -1 || distance[u] == inf)
            break;
        visited[u] = true;
        for (int v = 0; v < tot_loc; v++)
        {
            if (!visited[v] && graph[u][v] > 0)
            {
                if (distance[u] != inf && distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    new_line();
    print_line();
    cout << "\t DIJKSTRA - FASTEST RESCUE ROUTE" << endl;
    print_line();
    cout << "  From : " << locations[source].name << endl;
    cout << "  To   : " << locations[destination].name << endl;

    if (distance[destination] == inf)
    {
        cout << "\n  !! No reachable path found." << endl;
    }
    else
    {
        cout << "  Total Distance : " << distance[destination] << " km" << endl;
        cout << "\n  Rescue Route   : " << endl;
        cout << "  ";
        int path[max_loc];
        int pathLen = 0;
        int curr = destination;

        while (curr != -1)
        {
            path[pathLen++] = curr;
            curr = parent[curr];
        }
        for (int i = pathLen - 1; i >= 0; i--)
        {
            cout << locations[path[i]].name;
            if (i > 0)
                cout << "  -->  ";
        }
        cout << endl;
    }
    print_line();
}

// ekhn likhbo bellman ford er code

void run_bellman_ford(int source)
{
    int distance[max_loc];
    for (int i = 0; i < tot_loc; i++)
    {
        distance[i] = inf;
    }
    distance[source] = 0;

    for (int i = 0; i < tot_loc - 1; i++)
    {
        for (int k = 0; k < tot_loc; k++)
        {
            for (int j = 0; j < tot_loc; j++)
            {
                if (graph[k][j] > 0 && distance[k] != inf)
                {
                    if (distance[k] + graph[k][j] < distance[j])
                    {
                        distance[j] = distance[k] + graph[k][j];
                    }
                }
            }
        }
    }
    new_line();
    print_line();
    cout << "\t BELLMAN-FORD - ROUTE DAMAGE ANALYSIS" << endl;
    print_line();
    cout << "  Relief Base / Supply Centre: " << locations[source].name << endl;
    new_line();
    bool hasDamaged = false;
    for (int i = 0; i < tot_loc; i++)
    {
        for (int j = 0; j < tot_loc; j++)
        {
            if (graph[i][j] == -1)
                hasDamaged = true;
        }
    }
    if (hasDamaged)
    {
        cout << "  !! ALERT: One or more roads are FLOODED / DAMAGED." << endl;
        cout << "  Rescue vehicles must use alternate routes." << endl;
        new_line();
    }

    cout << "  Reachability from " << locations[source].name << ":" << endl;
    print_hy();

    for (int i = 0; i < tot_loc; i++)
    {
        cout << "   " << locations[i].name;
        int len = locations[i].name.length();
        for (int k = len; k < 25; k++)
            cout << " ";

        if (distance[i] == inf)
            cout << ": UNREACHABLE" << endl;
        else
            cout << ": " << distance[i] << " km" << endl;
    }

    new_line();
    cout << "  Flooded / Blocked Roads in Network:" << endl;
    print_hy();

    bool anyFound = false;
    for (int i = 0; i < tot_loc; i++)
    {
        for (int j = i + 1; j < tot_loc; j++)
        {
            if (graph[i][j] == -1)
            {
                cout << "  !! " << locations[i].name;
                int len = locations[i].name.length();
                for (int k = len; k < 16; k++)
                    cout << " ";

                cout << " <-->  " << locations[j].name << "  [FLOODED]" << endl;
                anyFound = true;
            }
        }
    }

    if (!anyFound)
        cout << "  All roads currently passable." << endl;
    print_line();
}
// prims algo
void run_prim_mst(int startNode)
{
    int key[max_loc];
    int parent[max_loc];
    bool mst[max_loc];

    for (int i = 0; i < tot_loc; i++)
    {
        key[i] = inf;
        mst[i] = false;
        parent[i] = -1;
    }

    key[startNode] = 0;

    for (int i = 0; i < tot_loc - 1; i++)
    {
        int u = minKey(key, mst);

        if (u == -1)
            break;
        mst[u] = true;

        for (int v = 0; v < tot_loc; v++)
        {
            if (graph[u][v] > 0 && !mst[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    new_line();
    print_line();
    cout << "\t PRIM'S ALGORITHM - MINIMUM RESCUE NETWORK" << endl;
    cout << "\t Base Camp : " << locations[startNode].name << endl;
    print_line();

    int totalCost = 0;
    for (int i = 0; i < tot_loc; i++)
    {
        if (parent[i] != -1)
        {
            cout << "  Connect: " << locations[parent[i]].name;
            int len1 = locations[parent[i]].name.length();
            for (int k = len1; k < 16; k++)
                cout << " ";

            cout << " <-->  " << locations[i].name;
            int len2 = locations[i].name.length();
            for (int k = len2; k < 16; k++)
                cout << " ";

            cout << " [" << key[i] << " km]" << endl;
            totalCost += key[i];
        }
    }

    new_line();
    cout << "  Minimum Network Connection Cost: " << totalCost << " km" << endl;
    print_line();
}

// kruskal mst er code ekhane (quick sort use kortesi)

void run_kruskal_mst()
{
    edge_item edges[max_edges];
    int idx = 0;

    for (int i = 0; i < tot_loc; i++)
    {
        for (int j = i + 1; j < tot_loc; j++)
        {
            if (graph[i][j] > 0)
            {
                edges[idx].src = i;
                edges[idx].dest = j;
                edges[idx].weight = graph[i][j];
                idx++;
            }
        }
    }
    QuickSort(edges, 0, idx - 1);

    new_line();
    print_line();
    cout << "\t KRUSKAL'S ALGORITHM - MINIMUM RESCUE NETWORK" << endl;
    cout << "\t (Edges Sorted via QuickSort | Shortest First)" << endl;
    print_line();

    int repre[max_loc];
    for (int i = 0; i < tot_loc; i++)
        repre[i] = i;

    int total_distance = 0;
    int edge_connected = 0;

    cout << "  Selected Routes (No Cycles Allowed):" << endl;
    print_hy();

    for (int i = 0; i < idx; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;
        if (repre[u] != repre[v])
        {
            cout << "  [+] " << locations[u].name;
            int len1 = locations[u].name.length();
            for (int k = len1; k < 16; k++)
                cout << " ";

            cout << " <-->  " << locations[v].name;
            int len2 = locations[v].name.length();
            for (int k = len2; k < 16; k++)
                cout << " ";

            cout << "[" << edges[i].weight << " km]" << endl;

            total_distance += edges[i].weight;
            edge_connected++;
            int old_rep = repre[v];
            int new_rep = repre[u];
            for (int j = 0; j < tot_loc; j++)
            {
                if (repre[j] == old_rep)
                {
                    repre[j] = new_rep;
                }
            }
        }
        if (edge_connected == tot_loc - 1)
            break;
    }

    new_line();
    cout << "  Total Minimum Connection Distance: " << total_distance << " km" << endl;
    print_line();
}

// eibar 0/1 knapsack kaj korbe

void run_knapsack(int capacity)
{
    if (capacity > 200)
        capacity = 200;
    int n = tot_rsc;
    static int dp[max_rsc + 1][201];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (resources[i - 1].weight <= w)
            {
                int include_item = resources[i - 1].value + dp[i - 1][w - resources[i - 1].weight];
                int skip_item = dp[i - 1][w];

                if (include_item > skip_item)
                    dp[i][w] = include_item;
                else
                    dp[i][w] = skip_item;
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    bool picked[max_rsc];
    for (int i = 0; i < max_rsc; i++)
        picked[i] = false;

    int current_w = capacity;
    for (int i = n; i > 0; i--)
    {
        if (dp[i][current_w] != dp[i - 1][current_w])
        {
            picked[i - 1] = true;
            current_w -= resources[i - 1].weight;
        }
    }

    new_line();
    print_line();
    cout << "\t KNAPSACK - OPTIMAL SUPPLY LOAD" << endl;
    cout << "\t Vehicle Capacity: " << capacity << " units" << endl;
    print_line();

    cout << "  Items LOADED for this mission:" << endl;
    print_hy();

    int usedWeight = 0, totalValue = 0;
    for (int i = 0; i < n; i++)
    {
        if (picked[i])
        {
            cout << "  [LOAD] " << resources[i].name;
            for (int k = resources[i].name.length(); k < 20; k++)
                cout << " ";

            cout << " Wt: " << resources[i].weight << "\tVal: " << resources[i].value << endl;
            usedWeight += resources[i].weight;
            totalValue += resources[i].value;
        }
    }
    new_line();
    cout << "  Items SKIPPED (Too heavy or low priority):" << endl;
    print_hy();
    for (int i = 0; i < n; i++)
    {
        if (!picked[i])
        {
            cout << "  [SKIP] " << resources[i].name;
            for (int k = resources[i].name.length(); k < 20; k++)
                cout << " ";
            cout << " Wt: " << resources[i].weight << "\tVal: " << resources[i].value << endl;
        }
    }

    new_line();
    cout << "  Final Summary:" << endl;
    cout << "  Total Weight  : " << usedWeight << " / " << capacity << " kg" << endl;
    cout << "  Total Priority: " << totalValue << endl;
    print_line();
}

// main menur design

void show_Menu()
{
    new_line();
    print_line();
    cout << "  Disaster Response & Resource Allocation System" << endl;
    ;
    print_line();
    cout << "    [1]  View Locations & Road Network" << endl;
    ;
    cout << "    [2]  Emergency Routing         (Dijkstra)" << endl;
    ;
    cout << "    [3]  Route Damage Report       (Bellman-Ford)" << endl;
    ;
    cout << "    [4]  Optimal Supply Load       (0/1 Knapsack)" << endl;
    ;
    cout << "    [5]  Rescue Network Planning   (Prim / Kruskal)" << endl;
    ;
    cout << "    [6]  Resources by Importance   (Merge Sort)" << endl;
    ;
    cout << "    [7]  Exit" << endl;
    ;
    print_line();
    cout << "    Enter choice: ";
}
//haha main function finally

int main()
{
    int choice;
    while (true)
    {
        show_Menu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            new_line();
            cout << "    [1] View Locations" << endl;
            cout << "    [2] View Road Connections" << endl;
            cout << "    Choice: ";
            int sub;
            cin >> sub;
            cin.ignore();

            if (sub == 1)
            {
                new_line();
                view_location();
            }
            else if (sub == 2)
            {
                new_line();
                view_road();
            }
            else
            {
                new_line();
                cout << "    Invalid option." << endl;
            }
        }
        else if (choice == 2)
        {
            new_line();
            cout << "  -- EMERGENCY ROUTING (Dijkstra) --" << endl;
            cout << "  (You can type approximate names - autocorrect is ON)" << endl;
            new_line();
            int src = get_location("  Source location      : ");
            int dest = get_location("  Destination location : ");
            run_dijkstra(src, dest);
        }
        else if (choice == 3)
        {
            new_line();
            cout << "  -- ROUTE DAMAGE ANALYSIS (Bellman-Ford) --" << endl;
            cout << "  (Autocorrect ON - type any location name)" << endl;
            new_line();
            int src = get_location("  Enter supply centre  : ");
            run_bellman_ford(src);
        }
        else if (choice == 4)
        {
            new_line();
            cout << "  -- OPTIMAL SUPPLY LOAD (0/1 Knapsack) --" << endl;
            cout << "  Enter vehicle capacity (e.g. 15, 20, 25): ";
            int cap;
            cin >> cap;
            cin.ignore();
            run_knapsack(cap);
        }
        else if (choice == 5)
        {
            new_line();
            cout << "  Select MST algorithm:" << endl;
            cout << "    [1] Prim    - expand from a chosen base camp" << endl;
            cout << "    [2] Kruskal - sort all roads (Quick Sort) then pick" << endl;
            cout << "    Choice: ";
            int sub;
            cin >> sub;
            cin.ignore();

            if (sub == 1)
            {
                new_line();
                cout << "  (Autocorrect ON)" << endl;
                int start = get_location("  Enter base camp : ");
                run_prim_mst(start);
            }
            else if (sub == 2)
            {
                new_line();
                run_kruskal_mst();
            }
            else
            {
                new_line();
                cout << "    Invalid option." << endl;
            }
        }
        else if (choice == 6)
        {
            new_line();
            view_rscby_priority();
        }
        else if (choice == 7)
        {
            new_line();
            cout << "  Stay safe. Relief teams are on the ground." << endl;
            cout << "  System shutting down." << endl;
            break;
        }
        else
        {
            new_line();
            cout << "  Invalid choice. Please enter 1-7." << endl;
        }
    }

    return 0;
}
