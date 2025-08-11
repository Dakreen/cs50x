#include <cs50.h>     // For get_int(), get_string(), and string type
#include <stdio.h>    // For printf()
#include <string.h>   // For strcmp()

// ===============================================================
// CS50x – Problem Set 3: Tideman Voting Algorithm
//
// Implements the Tideman (Ranked Pairs) method of ranked-choice voting.
// Given voter rankings, it:
// 1. Records preferences between every pair of candidates.
// 2. Creates ordered pairs where one candidate is preferred over another.
// 3. Sorts these pairs by strength of victory.
// 4. Locks them into a graph without creating cycles.
// 5. Declares the winner as the candidate with no incoming edges.
// ===============================================================

// Max number of candidates
#define MAX 9

// preferences[i][j] = number of voters who prefer candidate i over j
int preferences[MAX][MAX];

// locked[i][j] = true means candidate i is locked in over candidate j
bool locked[MAX][MAX];

// Struct for a winning/losing pair
typedef struct
{
    int winner;
    int loser;
} pair;

// Candidates and pairs arrays
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Global counts
int pair_count;         // Number of pairs stored
int candidate_count;    // Number of candidates

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
    // Validate command-line arguments
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate candidate array from argv[]
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

    // Initialize locked graph to false (no locked-in pairs yet)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Gather votes from each voter
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count]; // ranks[i] = candidate index of voter’s ith preference

        // Query voter for their ranked preferences
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // Record this voter's preferences into global matrix
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/*
 * vote:
 * Updates the ranks[] array for the current voter.
 * rank   → position in the voter's ranking (0 = first choice)
 * name   → candidate name entered by the voter
 * ranks[]→ array storing candidate indices in ranked order
 * Returns true if the vote is valid, false otherwise.
 */
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If entered name matches a candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // Prevent the same candidate being ranked twice
            if (rank > 0)
            {
                for (int j = 0; j < rank; j++)
                {
                    if (i == ranks[j])
                    {
                        return false;
                    }
                }
            }
            ranks[rank] = i;
            return true;
        }
    }
    return false; // Candidate name not found
}

/*
 * record_preferences:
 * Updates global preferences[][] based on a single voter's ranks[].
 * For every candidate ranked higher, increment preference over lower-ranked candidates.
 */
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

/*
 * add_pairs:
 * Creates an array of winning pairs where one candidate is preferred over another.
 * Skips ties (equal preference counts).
 */
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) // i beats j
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

/*
 * sort_pairs:
 * Sorts the pairs[] array in decreasing order of "strength of victory."
 * Strength of victory = preferences[winner][loser]
 * Uses merge sort for O(n log n) performance.
 */
void sort_pairs(void)
{
    merge_sort(pairs, pair_count);
}

/*
 * lock_pairs:
 * Locks pairs into the directed graph in sorted order,
 * skipping any that would create a cycle.
 */
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Only lock if it won't create a cycle
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

/*
 * print_winner:
 * The winner is the "source" of the graph: a candidate with no edges pointing at them.
 */
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i]) // No one beats candidate i here
            {
                count++;
            }
        }
        if (count == candidate_count) // Candidate never beaten
        {
            printf("%s\n", candidates[i]);
        }
    }
}

/*
 * merge_sort:
 * Recursively sorts an array of pairs by strength of victory (descending).
 */
void merge_sort(pair array[], int size)
{
    if (size == 1)
    {
        return; // Base case: single element
    }

    int mid = size / 2;
    int end = size - mid;

    // Split into left and right arrays
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

    // Sort each half
    merge_sort(left, mid);
    merge_sort(right, end);

    // Merge back together
    merge(size, mid, array, left, right);
}

/*
 * merge:
 * Merges two sorted arrays (left[] and right[]) into array[] in sorted order.
 */
void merge(int size, int mid, pair array[], pair left[], pair right[])
{
    int i = 0, j = 0, k = 0;
    while (i < size)
    {
        // If right array is empty, take from left
        if (k == size - mid)
        {
            array[i++] = left[j++];
        }
        // If left array is empty, take from right
        else if (j == mid)
        {
            array[i++] = right[k++];
        }
        // Compare strength of victory and pick larger
        else if (preferences[left[j].winner][left[j].loser] >
                 preferences[right[k].winner][right[k].loser])
        {
            array[i++] = left[j++];
        }
        else
        {
            array[i++] = right[k++];
        }
    }
}

/*
 * check_cycle:
 * Detects if locking a given pair would create a cycle in the graph.
 * Uses recursion to follow the chain of locked edges.
 */
bool check_cycle(int winner, int loser)
{
    if (loser == winner) // Cycle detected
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) // Follow edge from loser to next candidate
        {
            if (check_cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false; // No cycle found
}
