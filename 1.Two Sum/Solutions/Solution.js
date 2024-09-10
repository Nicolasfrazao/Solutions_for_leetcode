//Solution in Javascript

/**
 * This function takes an array of numbers and a target number as arguments.
 * It will return an array containing the indices of the two numbers in the input
 * array that add up to the target number.
 * If no two numbers in the array add up to the target, it will return an empty array.
 */
var BruteForce = function(nums, target) {
    //Iterate over the array, comparing each number with every other number
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            //If the sum of the two numbers is equal to the target, return their indices
            if (nums[i] + nums[j] == target) {
                return [i, j];
            }
        }
    }
    //If no two numbers added up to the target, return an empty array
    return [];
};

//------------------------------------------------------------------------//

/**
 * This function takes an array of numbers and a target number as arguments.
 * It will return an array containing the indices of the two numbers in the input
 * array that add up to the target number.
 * If no two numbers in the array add up to the target, it will return an empty array.
 * This function uses a hash map to store the numbers in the array, along with their
 * indices. It then iterates over the array, and for each number, it checks if the
 * difference between the target and that number exists in the hash map. If it does,
 * it returns the indices of the two numbers that add up to the target.
 */
var optimalSolution = function(nums, target) {

    let map = {}
    for(let i = 0 ; i < nums.length ; i++){
        //Calculate the difference between the target and the current number
        let diff = target-nums[i]
        //If the difference exists in the hash map, return the indices of the two
        //numbers that add up to the target
        if(diff in map){
            return [map[diff] , i]
        }
        //If the difference does not exist in the hash map, add the current number
        //and its index to the hash map
        map[nums[i]] = i 
    }
};

