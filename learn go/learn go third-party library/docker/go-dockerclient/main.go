package main

import (
	"fmt"

	docker "github.com/fsouza/go-dockerclient"
)

func main() {
	client, err := docker.NewClientFromEnv()
	if err != nil {
		panic(err)
	}

	images, err := client.ListImages(docker.ListImagesOptions{})
	if err != nil {
		panic(err)
	}
	for _, image := range images {
		fmt.Println(image)
	}

	containers, err := client.ListContainers(docker.ListContainersOptions{})
	if err != nil {
		panic(err)
	}
	for _, container := range containers {
		fmt.Println(container)
	}
}