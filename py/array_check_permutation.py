import pytest


def is_permutation(input, permutation):
    return sorted(input) == sorted(permutation)


def test_is_permutation():
    a = [1, 2, 3]
    b = [2, 1, 3]

    assert is_permutation(a, b)


def test_is_not_permutation_same_size():
    a = [1, 2, 3]
    b = [2, 1, 4]

    assert not is_permutation(a, b)


def test_is_not_permutation_diff_size():
    a = [1, 2, 3]
    b = [1, 2, 3, 4]

    assert not is_permutation(a, b)


def test_empty_permutation():
    assert is_permutation([], [])

