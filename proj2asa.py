class Edge:
    def __init__(self, v1, v2, w):
        self.v1 = v1
        self.v2 = v2
        self.w = w


# Global variable
res = 0


def init_vertex_vector(v):
    vv_parent = list(range(1, v + 1))
    return vv_parent


def get_edges(e):
    e_vec = []
    for _ in range(e):
        v1, v2, w = map(int, input().split())
        e_vec.append(Edge(v1, v2, w))
    return e_vec


# Tree forest functions
def find_set(v, vv_parent):
    if vv_parent[v - 1] != v:
        vv_parent[v - 1] = find_set(vv_parent[v - 1], vv_parent)
    return vv_parent[v - 1]


def link_set(v1, v2, vv_parent, vv_rank):
    if vv_rank[v1 - 1] > vv_rank[v2 - 1]:
        vv_parent[v2 - 1] = v1
    else:
        vv_parent[v1 - 1] = v2
        if vv_rank[v1 - 1] == vv_rank[v2 - 1]:
            vv_rank[v2 - 1] += 1


def union_set(v1, v2, vv_parent, vv_rank):
    link_set(find_set(v1, vv_parent), find_set(v2, vv_parent), vv_parent, vv_rank)


# Kruskal
def kruskal(e, e_vec, vv_parent, vv_rank):
    global res
    for i in range(e):
        if find_set(e_vec[i].v1, vv_parent) != find_set(e_vec[i].v2, vv_parent):
            res += e_vec[i].w
            union_set(e_vec[i].v1, e_vec[i].v2, vv_parent, vv_rank)


def comparator(e1, e2):
    return e1.w > e2.w


def main():
    v, e = map(int, input().split())  # Get #vertices and #edges

    vv_parent = init_vertex_vector(v)
    e_vec = get_edges(e)
    vv_rank = [0] * v

    e_vec.sort(key=lambda x: x.w, reverse=True)

    kruskal(e, e_vec, vv_parent, vv_rank)

    print(res)


if __name__ == "__main__":
    main()