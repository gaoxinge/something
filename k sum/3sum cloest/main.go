package main

import (
	"sort"
	"fmt"
)

func abs(a, b int) int {
	if a > b {
		return a - b
	} else {
		return b - a
	}
}

func threeSum(nums []int, target int) int {
	result := nums[0] + nums[1] + nums[2]
	sort.Ints(nums)

	for i, num := range nums {
		if i > 0 && num == nums[i - 1] {
			continue
		}


		start := i + 1
		end := len(nums) - 1
		if start >= end {
			break
		}
		temp := num + nums[start] + nums[end]

		for start < end {
			r := num + nums[start] + nums[end]

			if r < target {
				start++
			} else if r > target {
				end--
			}
			fmt.Println(num, nums[start], nums[end], abs(r, target) < abs(temp, target))
			if abs(r, target) < abs(temp, target) {
				temp = r
			}

			if abs(r, target) == 0 {
				break
			}
		}

		if abs(temp, target) < abs(result, target) {
			result = temp
		}

		if abs(temp, target) == 0 {
			break
		}
	}

	return result
}

func main() {
	fmt.Println(threeSum([]int{-3, -2, -5, 3, -4}, -1))
}