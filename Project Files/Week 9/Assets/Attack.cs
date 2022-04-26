using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Attack : StateMachineBehaviour
{

    GameObject Player;
    GameObject Enemy;
    public Material red;
  
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        Player = GameObject.FindGameObjectWithTag("Player");
        Enemy = animator.gameObject;
        Renderer[] eyes = Enemy.GetComponentsInChildren<Renderer>();
        eyes[1].material = red;
        eyes[2].material = red;
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        Vector3 direction = Player.transform.position - Enemy.transform.position;
        Enemy.transform.rotation =
            Quaternion.Slerp(Enemy.transform.rotation,
                Quaternion.LookRotation(direction), 5.0f * Time.deltaTime);
        Enemy.transform.Translate(0, 0, 5.0f * Time.deltaTime);
    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {

    }

}
