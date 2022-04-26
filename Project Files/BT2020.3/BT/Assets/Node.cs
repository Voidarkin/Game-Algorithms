using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node  {
    public BehaviorTree tree;
    public List<Node> children;
    public int currentChild;

    public Node()
    {
        children = new List<Node>();
    }
    public virtual NodeResult Execute()
    {
        return NodeResult.FAILURE;
    }

    public virtual void SetChildResult(NodeResult result)
    {
    }

    public virtual void Reset()
    {
        currentChild = -1;
    }
}
