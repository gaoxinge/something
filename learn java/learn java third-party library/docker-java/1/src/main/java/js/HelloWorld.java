package js;

import com.github.dockerjava.api.DockerClient;
import com.github.dockerjava.api.model.Container;
import com.github.dockerjava.api.model.Image;
import com.github.dockerjava.core.DockerClientBuilder;

import java.util.List;

public class HelloWorld {
    public static void main(String[] args) {
        DockerClient dockerClient = DockerClientBuilder.getInstance().build();

        List<Image> images = dockerClient.listImagesCmd().exec();
        for (Image image: images) {
            System.out.println(image);
        }

        List<Container> containers = dockerClient.listContainersCmd().exec();
        for (Container container: containers) {
            System.out.println(container);
        }
    }
}
