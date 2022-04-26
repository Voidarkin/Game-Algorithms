using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Attack : StateMachineBehaviour
{
    LineRenderer line;
    GameObject player;
    float timeToChangeBolt = 0.5f;
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        player = GameObject.FindGameObjectWithTag("Player");
        line = animator.gameObject.GetComponent<LineRenderer>();
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        timeToChangeBolt -= Time.deltaTime;
        if (timeToChangeBolt < 0)
        {
            timeToChangeBolt = 0.5f;
            line.positionCount = 20;
            Vector3 ep = animator.gameObject.transform.position;
            Vector3 pp = player.transform.position;
            Vector3 dir = (pp - ep) / 20.0f;
            for (int i = 0; i < 20; i++)
            {
                line.SetPosition(i, ep + dir * i + Random.insideUnitSphere * 0.3f);
            }
        }
    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        line.positionCount = 0;
    }


}
