using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnObstacle : MonoBehaviour
{
    public GameObject SpawnPrefab;
    public float spawnRate = 0.5f;
    public float elapsedTime;
    // Start is called before the first frame update
    void Start()
    {
        elapsedTime = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        elapsedTime += Time.deltaTime;
        if (elapsedTime > spawnRate)
        {
            elapsedTime = 0.0f;
            GameObject.Instantiate(SpawnPrefab, Random.insideUnitSphere * 40.0f, Quaternion.identity);
        }
    }
}
