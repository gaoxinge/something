package js;

import com.spotify.docker.client.DefaultDockerClient;
import com.spotify.docker.client.DockerClient;
import com.spotify.docker.client.messages.Container;
import com.spotify.docker.client.messages.Image;

import java.util.*;

public class HelloWorld {
    public static void main(String[] args) throws Exception {
        DockerClient docker = DefaultDockerClient.fromEnv().build();

        List<Image> images = docker.listImages();
        for (Image image: images) {
            System.out.println(image);
        }

        List<Container> containers = docker.listContainers();
        for (Container container: containers) {
            System.out.println(container);
        }
    }
}
