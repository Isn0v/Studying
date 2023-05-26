import queue

def bfs(start, color, graph):
    q = queue.SimpleQueue()
    q.put(start)
    
    while not q.empty():
        node = q.get()
        
        for it in graph[node]:
            if color[it] == -1:
                color[it] = not color[node]
                q.put(it)
            elif color[it] == color[node]:
                return False
        return True
    
def isBipartite(self, graph: list[list[int]]) -> bool:
    n = len(graph)
    color = [-1]*n
    
    for i in range(n):
        if not bfs(i, color, graph):
            return False
    return True