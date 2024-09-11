//Solution for C#

public class Solution {

    /// <summary>
    /// The brute force solution is to check every possible pair of numbers in the array
    /// to see if they sum to the target. This is a very inefficient solution, requiring
    /// O(n^2) time complexity, but it is simple to understand and implement.
    /// </summary>
    public int[] BruteForce(int[] nums, int target) {

        // loop through the array and check every possible pair of numbers
        for (int i = 0; i < nums.Length; i++) {
            for (int j = i + 1; j < nums.Length; j++) {

                // if the two numbers sum to the target, return their indices
                if (nums[i] + nums[j] == target) {
                    return new int[] { i, j };
                }
            }
        }

        // if no pair of numbers sum to the target, return -1, -1
        return new int[] { -1, -1 };
    }


    /// <summary>
    /// The two pass hash table solution is to create a dictionary of the numbers in the array
    /// and their indices. Then, for each number in the array, check if the complement (target - number)
    /// is in the dictionary. If it is, return the indices of the two numbers. This solution has O(n) time
    /// complexity, making it much more efficient than the brute force solution.
    /// </summary>
    public int[] TwoPassHashTable(int[] nums, int target) {

        // create a dictionary of the numbers in the array and their indices
        Dictionary<int, int> numIndices = new Dictionary<int, int>();

        // loop through the array and add each number to the dictionary
        for (int i = 0; i < nums.Length; i++ ) {

            // calculate the complement of the current number
            int complement = target - nums[i];

            // if the complement is in the dictionary, return the indices of the two numbers
            if (map.ContainsKey(complement)) {
                return new int[] { map[complement], i };
            }

            // add the current number to the dictionary
            map[nums[i]] = i;
        }

        // if no two numbers sum to the target, throw an exception
        throw new Exeption("No two sum solution");
    }
}
