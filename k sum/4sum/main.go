package main

import (
	"sort"
	"fmt"
)

func fourSum(nums []int, target int) [][]int {
	results := [][]int{}
	sort.Ints(nums)

	for i := 0; i < len(nums); i++ {
		if i > 0 && nums[i] == nums[i - 1] {
			continue
		}

		for j := i + 1; j < len(nums); j++ {
			if j > i + 1 && nums[j] == nums[j - 1] {
				continue
			}

			s := j + 1
			e := len(nums) - 1
			for s < e {
				r := nums[i] + nums[j] + nums[s] + nums[e]
				if r == target {
					result := []int{nums[i], nums[j], nums[s], nums[e]}
					results = append(results, result)
					for s < e && nums[s] == nums[s + 1] {
						s++
					}
					for s < e && nums[e] == nums[e - 1] {
						e--
					}
					s++
					e--
				} else if r < target {
					s++
				} else {
					e--
				}
			}
		}
	}

	return results
}

func main() {
	fmt.Println(fourSum([]int{1, 0, -1, 0, -2, 2}, 0))
}