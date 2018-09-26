// O(n ^ 3)   n
// O(n ^ 2)   y
// O(n ^ 2)   n


func threeSum(nums []int) [][]int {
	results := [][]int{}
	sort.Ints(nums)

	for i, target := range nums {
		if i > 0 && target == nums[i - 1] {
			continue
		}

		start := i + 1
		end := len(nums) - 1
		for start < end {
			r := target + nums[start] + nums[end]
			if r == 0 {
				result := []int{target, nums[start], nums[end]}
				results = append(results, result)

				for start < end && nums[start] == nums[start + 1] {
					start++
				}
				for start < end && nums[end] == nums[end - 1] {
					end--
				}

				start++
				end--
			} else if r < 0 {
				start++
			} else {
				end--
			}
		}
	}

	return results
}