typedef struct TreeNode {
  TreeNode *parent;
} TreeNode_t;

TreeNode *findFirstCommonAncestor(TreeNode *this, TreeNode *other) {
  if (!this || !other)
    return NULL;
  
  int thisDepth = depth(this);
  int otherDepth = depth(other);

  TreeNode *thisNew = (thisDepth <= otherDepth ? this : nthParent(this, thisDepth-otherDepth));
  TreeNode *otherNew = (otherDepth <= thisDepth ? other : nthParent(other, otherDepth-thisDepth));
  
  return findFirstCommonAncestorHelper(thisNew, otherNew);
}

TreeNode *findFirstCommonAncestorHelper(TreeNode *this, TreeNode *other) {
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

int depth(TreeNode *node) {
  if (!node)
    return 0;
  else
    return 1 + depth(node->parent);
}

TreeNode *nthParent(TreeNode *node, int num) {
  if (!num)
    return node;
  else
    return nthParent(node->parent, num-1);
}
