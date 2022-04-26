using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BehaviorTree : MonoBehaviour {
    Stack<Node> CallStack;
    Hashtable Blackboard;
    public Node root;
    // Use this for initialization
    void Awake()
    {
        CallStack = new Stack<Node>();
        Blackboard = new Hashtable();
    }

	// Update is called once per frame
	public virtual void Update () {
        RunStack();
	}

    public void AddKey(string key)
    {
        if (Blackboard.ContainsKey(key) == false)
        {
            Blackboard.Add(key, null);
        }
    }

    public object GetValue(string key)
    {
        if (Blackboard.ContainsKey(key))
        {
            return Blackboard[key];
        }
        else
        {
            return null;
        }
    }

    public void SetValue(string key, object value)
    {
        Blackboard[key] = value;
    }

    public void PushNode(Node node)
    {
        node.Reset();
        node.tree = this;
        CallStack.Push(node);
    }

    void RunStack()
    {
        if (CallStack.Count == 0)
        {
            // stack is empty - add to it
            PushNode(root);
        }

        Node top = CallStack.Peek();
        NodeResult result = top.Execute();
        switch (result)
        {
            case NodeResult.FAILURE:
            case NodeResult.SUCCESS:
                CallStack.Pop(); // remove this node
                if (CallStack.Count == 0)
                {
                    return;
                }
                Node parent = CallStack.Peek();
                parent.SetChildResult(result);
                RunStack(); // and let the parent node continue
                break;
            case NodeResult.RUNNING:
                return; // we do not need to do anything in this case.
                        // we will continue with this node in the next frame.
            case NodeResult.STACKED:
                RunStack(); // let the newly added child node have some CPU
                break;
            default:
                break;
        }
    }
}
