// O(n^2)         y
// O(n * log(n))  n
// O(n)           y


func twoSum(nums []int, target int) []int {
    for i := 0; i < len(nums) - 1; i++ {
        for j := i + 1; j < len(nums); j++ {
            if nums[i] + nums[j] == target {
                return []int{i, j}
            }
        }
    }
    return nil
}



func twoSum(nums []int, target int) []int {
    m := map[int]int{}
    for i, num1 := range nums {
        num2 := target - num1
        if j, ok := m[num2]; ok {
            return []int{j, i}
        }
        m[num1] = i
    }
    return nil
}