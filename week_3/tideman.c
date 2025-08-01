#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is the number of voters who prefer candidate i over candidate j
int preferences[MAX][MAX];

// locked[i][j] means candidate i is locked in over candidate j (true if i beats j in final graph)
bool locked[MAX][MAX];

// Struct representing a winning pair
typedef struct
{
    int winner;
    int loser;
} pair;

// Candidate names and pair storage
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; // Max number of pairs in a complete graph

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(pair array[], int size);
void merge(int size, int mid, pair array[], pair left[], pair right[]);
bool check_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for valid usage: at least one candidate must be provided
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Initialize candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Initialize locked graph to false (no pairs locked yet)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

    // Get voter count
    int voter_count = get_int("Number of voters: ");

    // For each voter
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count]; // ranks[i] = candidate index ranked at position i

        // Query each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) // validate vote
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // Update global preferences matrix
        record_preferences(ranks);

        printf("\n");
    }

    // Process election
    add_pairs();     // Identify all winning pairs
    sort_pairs();    // Sort pairs by strength of victory
    lock_pairs();    // Lock in pairs, avoiding cycles
    print_winner();  // Output the winner

    return 0;
}

// Process a single voter's vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Prevent duplicate rankings
            for (int j = 0; j < rank; j++)
            {
                if (i == ranks[j])
                {
                    return false;
                }
            }
            ranks[rank] = i;
            return true;
        }
    }
    return false; // name not found
}

// Update preferences matrix for one voter's rankings
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Identify all winning pairs (only one per i vs. j duel)
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs by strength of victory (descending order)
// Uses merge sort for stability and efficiency
void sort_pairs(void)
{
    merge_sort(pairs, pair_count);
}

// Lock in pairs one by one, avoiding cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Only lock if it does not create a cycle
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner (source of the graph)
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

// Recursive merge sort
void merge_sort(pair array[], int size)
{
    if (size == 1)
    {
        return;
    }

    int mid = size / 2;
    int end = size - mid;

    pair left[mid];
    pair right[end];

    for (int i = 0; i < mid; i++)
    {
        left[i] = array[i];
    }
    for (int i = 0; i < end; i++)
    {
        right[i] = array[i + mid];
    }

    merge_sort(left, mid);
    merge_sort(right, end);

    merge(size, mid, array, left, right);
}

// Merge step of merge sort
void merge(int size, int mid, pair array[], pair left[], pair right[])
{
    int i = 0, j = 0, k = 0;

    while (i < size)
    {
        if (k == size - mid)
        {
            array[i++] = left[j++];
        }
        else if (j == mid)
        {
            array[i++] = right[k++];
        }
        else if (preferences[left[j].winner][left[j].loser] > preferences[right[k].winner][right[k].loser])
        {
            array[i++] = left[j++];
        }
        else
        {
            array[i++] = right[k++];
        }
    }
}

// Check recursively if locking this pair would create a cycle
bool check_cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true; // Cycle detected
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (check_cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false; // No cycle
}
