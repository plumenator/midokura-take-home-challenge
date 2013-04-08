#import <stdio.h>
#import <assert.h>

typedef struct TreeNode {
  struct TreeNode *parent;
} TreeNode_t;

TreeNode_t *findFirstCommonAncestor(TreeNode_t *this, TreeNode_t *other);
TreeNode_t *findFirstCommonAncestorHelper(TreeNode_t *this, TreeNode_t *other);
int depth(TreeNode_t *node);
TreeNode_t *nthParent(TreeNode_t *node, int num);

TreeNode_t *findFirstCommonAncestor(TreeNode_t *this, TreeNode_t *other) {
  if (!this || !other)
    return NULL;
  
  int thisDepth = depth(this);
  int otherDepth = depth(other);

  TreeNode_t *thisNew = (thisDepth <= otherDepth ? this : nthParent(this, thisDepth-otherDepth));
  TreeNode_t *otherNew = (otherDepth <= thisDepth ? other : nthParent(other, otherDepth-thisDepth));
  
  return findFirstCommonAncestorHelper(thisNew, otherNew);
}

TreeNode_t *findFirstCommonAncestorHelper(TreeNode_t *this, TreeNode_t *other) {
  if (this == other)
    {
      return this;
    }
  else
    {
      assert(this && other);
      return findFirstCommonAncestorHelper(this->parent, other->parent);
    }
}

int depth(TreeNode_t *node) {
  if (!node)
    return 0;
  else
    return 1 + depth(node->parent);
}

TreeNode_t *nthParent(TreeNode_t *node, int num) {
  if (!num)
    return node;
  else
    return nthParent(node->parent, num-1);
}

typedef struct MyTreeNode {
  TreeNode_t node;
  char data[100];
} MyTreeNode_t;

void test1() {
  MyTreeNode_t root = {{NULL}, "R"};
  MyTreeNode_t a = {{(TreeNode_t *)&root}, "A"};
  MyTreeNode_t b = {{(TreeNode_t *)&root}, "B"};

  printf("%s: The first common ancestor of %s and %s is %s\n",
	 __func__,
	 a.data,
	 b.data,
	 ((MyTreeNode_t *)findFirstCommonAncestor((TreeNode_t *)&a, (TreeNode_t *)&b))->data);
}

void test2() {
  MyTreeNode_t root = {{NULL}, "R"};
  MyTreeNode_t a = {{(TreeNode_t *)&root}, "A"};
  MyTreeNode_t b = {{(TreeNode_t *)&root}, "B"};
  MyTreeNode_t c = {{(TreeNode_t *)&b}, "C"};

  printf("%s: The first common ancestor of %s and %s is %s\n",
	 __func__,
	 a.data,
	 c.data,
	 ((MyTreeNode_t *)findFirstCommonAncestor((TreeNode_t *)&a, (TreeNode_t *)&c))->data);
}

void test3() {
  MyTreeNode_t root = {{NULL}, "R"};
  MyTreeNode_t a = {{(TreeNode_t *)&root}, "A"};
  MyTreeNode_t b = {{(TreeNode_t *)&root}, "B"};
  MyTreeNode_t c = {{(TreeNode_t *)&a}, "C"};
  MyTreeNode_t d = {{(TreeNode_t *)&a}, "D"};
  MyTreeNode_t e = {{(TreeNode_t *)&b}, "E"};
  MyTreeNode_t f = {{(TreeNode_t *)&b}, "F"};
  MyTreeNode_t g = {{(TreeNode_t *)&f}, "G"};
  MyTreeNode_t h = {{(TreeNode_t *)&f}, "H"};
  MyTreeNode_t i = {{(TreeNode_t *)&f}, "I"};

  printf("%s: The first common ancestor of %s and %s is %s\n",
	 __func__,
	 d.data,
	 i.data,
	 ((MyTreeNode_t *)findFirstCommonAncestor((TreeNode_t *)&d, (TreeNode_t *)&i))->data);
}

void test4() {
  MyTreeNode_t root = {{NULL}, "R"};
  MyTreeNode_t a = {{(TreeNode_t *)&root}, "A"};
  MyTreeNode_t b = {{(TreeNode_t *)&root}, "B"};
  MyTreeNode_t c = {{(TreeNode_t *)&a}, "C"};
  MyTreeNode_t d = {{(TreeNode_t *)&a}, "D"};
  MyTreeNode_t e = {{(TreeNode_t *)&b}, "E"};
  MyTreeNode_t f = {{(TreeNode_t *)&b}, "F"};
  MyTreeNode_t g = {{(TreeNode_t *)&f}, "G"};
  MyTreeNode_t h = {{(TreeNode_t *)&f}, "H"};
  MyTreeNode_t i = {{(TreeNode_t *)&f}, "I"};

  printf("%s: The first common ancestor of %s and %s is %s\n",
	 __func__,
	 e.data,
	 f.data,
	 ((MyTreeNode_t *)findFirstCommonAncestor((TreeNode_t *)&e, (TreeNode_t *)&f))->data);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
