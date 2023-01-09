import hashlib
from abc import ABC, abstractmethod
from typing import Optional


def generate_hash1(m):
    def hash1(e: str):
        return hash(hashlib.md5(e.encode("utf-8")).digest()[:6]) % m
    return hash1


def generate_hash2(m):
    def hash2(e: str):
        return hash(hashlib.sha256(e.encode("utf-8")).digest()[:6]) % m
    return hash2


class Filter(ABC):

    @abstractmethod
    def put(self, e: str):
        raise NotImplementedError

    @abstractmethod
    def get(self, e: str) -> Optional[float]:
        raise NotImplementedError


class BloomFilter(Filter):

    def __init__(self, m):
        self.m = m
        self.n = 0
        self.array = [0 for _ in range(m)]
        self.hash1 = generate_hash1(m)
        self.hash2 = generate_hash2(m)

    def put(self, e: str):
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        self.array[hash1] = 1
        self.array[hash2] = 1

    def get(self, e: str) -> Optional[float]:
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        if self.array[hash1] == 0 or self.array[hash2] == 0:
            return None
        p = (1 - (1 - 1 / self.m) ** (2 * self.n)) ** 2
        return p


class CountBloomFilter(Filter):

    def __init__(self, m):
        self.m = m
        self.n = 0
        self.array = [0 for _ in range(m)]
        self.hash1 = generate_hash1(m)
        self.hash2 = generate_hash2(m)

    def put(self, e: str):
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        self.array[hash1] += 1
        self.array[hash2] += 1

    def get(self, e: str) -> Optional[float]:
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        if self.array[hash1] == 0 or self.array[hash2] == 0:
            return None
        p = (1 - (1 - 1 / self.m) ** (2 * self.n)) ** 2
        return p

    def delete(self, e: str):
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        if self.array[hash1] > 0 and self.array[hash2] > 0:
            self.array[hash1] -= 1
            self.array[hash2] -= 1


class PartitionBloomFilter(Filter):

    def __init__(self, m):
        self.m = m
        self.n = 0
        self.array = [[0 for _ in range(m)] for _ in range(2)]
        self.hash1 = generate_hash1(m)
        self.hash2 = generate_hash2(m)

    def put(self, e: str):
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        self.array[0][hash1] = 1
        self.array[0][hash2] = 1

    def get(self, e: str) -> Optional[float]:
        hash1 = self.hash1(e)
        hash2 = self.hash2(e)
        if self.array[0][hash1] == 0 or self.array[0][hash2] == 0:
            return None
        p = (1 - (1 - 1 / self.m) ** self.n) ** 2
        return p

