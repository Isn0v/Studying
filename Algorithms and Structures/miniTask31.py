def longestCycle(self, edges: list[int]) -> int:
    res = -1
    for i in range(len(edges)):
        cur = i
        path = []
        while edges[cur] >= 0:
            path.append(cur)
            _next = edges[cur]
            edges[cur] = -1
            cur = _next
        if cur in path:
            res = max(res, len(path) - path.index(cur))
    return res