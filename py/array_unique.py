def all_unique(input):
    found = {}
    for element in input:
        if element in found:
            return False
        found[element] = 1
    return True


def test_no_duplicates():
    no_duplicates = [1, 2, 3, 4, 5]
    assert all_unique(no_duplicates)


def test_duplicates():
    duplicates = [1, 2, 3, 3, 3, 4]
    assert not all_unique(duplicates)


def test_empty():
    assert all_unique([])
