typedef struct TreeNode {
  TreeNode *parent;
} TreeNode_t;

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
