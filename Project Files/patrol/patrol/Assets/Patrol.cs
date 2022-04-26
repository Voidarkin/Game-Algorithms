using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Patrol : StateMachineBehaviour
{
    GameObject[] waypoints;
    int currentWP = 0;
    GameObject Enemy;
    private void Awake()
    {
        waypoints = GameObject.FindGameObjectsWithTag("waypoint");
    }
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        Enemy = animator.gameObject;
        if (waypoints.Length == 0)
        {
            return;
        }
        currentWP = 0;
        float distance = Vector3.Distance(waypoints[0].transform.position, Enemy.transform.position);
        for (int i = 1; i < waypoints.Length; i++)
        {
            float dis = Vector3.Distance(waypoints[i].transform.position, Enemy.transform.position);
            if (dis < distance)
            {
                distance = dis;
                currentWP = i;
            }
        }
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if (waypoints.Length == 0)
        {
            return;
        }
        if (Vector3.Distance(waypoints[currentWP].transform.position, Enemy.transform.position) < 3.0f)
        {
            currentWP++;
            if (currentWP >= waypoints.Length)
            {
                currentWP = 0;
            }
        }
        Vector3 direction = waypoints[currentWP].transform.position - Enemy.transform.position;
        Enemy.transform.rotation =
            Quaternion.Slerp(Enemy.transform.rotation,
            Quaternion.LookRotation(direction), 1.0f * Time.deltaTime);
        Enemy.transform.Translate(0, 0, 2.0f * Time.deltaTime);
    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {

    }

}
