use std::io;
use std::cmp;

//static mut height: i32 = -1;
//static mut width: i32 = -1;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

#[derive(Debug)]
struct Agent
{
    id: i32,
    player: i32,
    x: i32,
    y: i32,
    cooldown: i32, // Number of turns before this agent can shoot
    splash_bombs: i32,
    wetness: i32, // Damage (0-100) this agent has taken
    optimal_range: i32, // Maximum manhattan distance for greatest damage output
    soaking_power: i32, // Damage output within optimal conditions
}

#[derive(Debug)]
struct Tile
{
    x: i32,
    y: i32,
    cover: i32,
}

fn update_agent(agents: &mut Vec<Agent>, id: i32, x: i32, y: i32, cooldown: i32, splash_bombs: i32, wetness: i32)
{
    let mut i: usize = 0;
    while agents[i].id != id
    {
        i += 1;
    }
    agents[i].x = x;
    agents[i].y = y;
    agents[i].cooldown = cooldown;
    agents[i].splash_bombs = splash_bombs;
    agents[i].wetness = wetness;
}

fn get_distance(agent_1: &Agent, agent_2: &Agent) -> i32
{
    return
    (cmp::max(agent_1.x, agent_2.x) - cmp::min(agent_1.x, agent_2.x))
    + (cmp::max(agent_1.y, agent_2.y) - cmp::min(agent_1.y, agent_2.y))
}

fn main() {
    let mut debug = 1;
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let my_id = parse_input!(input_line, i32); // Your player id (0 or 1)
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let agent_count = parse_input!(input_line, i32); // Total number of agents in the game
    let mut agents: Vec<Agent> = vec![];
    for i in 0..agent_count as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split(" ").collect::<Vec<_>>();
        let id = parse_input!(inputs[0], i32); // Unique identifier for this agent
        let player = parse_input!(inputs[1], i32); // Player id of this agent
        let shoot_cooldown = parse_input!(inputs[2], i32); // Number of turns between each of this agent's shots
        let optimal_range = parse_input!(inputs[3], i32); // Maximum manhattan distance for greatest damage output
        let soaking_power = parse_input!(inputs[4], i32); // Damage output within optimal conditions
        let splash_bombs = parse_input!(inputs[5], i32); // Number of splash bombs this can throw this game
        agents.extend([Agent{id, player, x: -1, y: -1, cooldown: shoot_cooldown,
            splash_bombs, wetness: 0, optimal_range, soaking_power,}])
    }
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let inputs = input_line.split(" ").collect::<Vec<_>>();
    let mut width = parse_input!(inputs[0], i32); // Width of the game map
    let mut height = parse_input!(inputs[1], i32); // Height of the game map
    let mut grid: Vec<Tile> = vec![];
    for i in 0..height as usize
    {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split_whitespace().collect::<Vec<_>>();
        for j in 0..width as usize
        {
            let x = parse_input!(inputs[3*j], i32); // X coordinate, 0 is left edge
            let y = parse_input!(inputs[3*j+1], i32); // Y coordinate, 0 is top edge
            let tile_type = parse_input!(inputs[3*j+2], i32);
            grid.extend([Tile{x, y, cover: tile_type,}]);
        }
    }

    // game loop
    loop {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let agent_count = parse_input!(input_line, i32);
        for i in 0..agent_count as usize {
            let mut input_line = String::new();
            io::stdin().read_line(&mut input_line).unwrap();
            let inputs = input_line.split(" ").collect::<Vec<_>>();
            let id = parse_input!(inputs[0], i32);
            let x = parse_input!(inputs[1], i32);
            let y = parse_input!(inputs[2], i32);
            let cooldown = parse_input!(inputs[3], i32); // Number of turns before this agent can shoot
            let splash_bombs = parse_input!(inputs[4], i32);
            let wetness = parse_input!(inputs[5], i32); // Damage (0-100) this agent has taken
            update_agent(&mut agents, id, x, y, cooldown, splash_bombs, wetness);
//          agents.extend([Agent{id, player: -1, x, y, cooldown, splash_bombs, wetness, optimal_range: -1, soaking_power: -1,}])
        }
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let my_agent_count = parse_input!(input_line, usize); // Number of alive agents controlled by you
        eprintln!("agents {}, mine {}, len {}", agent_count, my_agent_count, agents.len());
        for k in 0..height
        {
            for l in 0..width
            {
                if grid[(k * width + l) as usize].cover > 0
                {
                    eprintln!("{}:{} : {}", l, k, grid[(k * width + l) as usize].cover);
                }
            }
        }
        for j in 0..agent_count as usize
        {
            //eprintln!("my_id: {}, agent[{}]: {:?}", my_id, j, agents[j]);
            if agents[j].player == my_id
            {
                //eprintln!("agent_count: {}", agent_count);
                let mut wet: i32 = -1;
                let mut shoot_id: i32 = -1;
                let mut cover: i32 = 42;
                let mut move_x: i32 = agents[j].x;
                let mut move_y: i32 = agents[j].y;
                for i in 0..agent_count as usize
                {
                    if agents[i].player != my_id && get_distance(&(agents[j]), &(agents[i])) <= agents[j].optimal_range
                    {
                        if agents[j].x < agents[i].x
                        {
                            eprintln!("agent: {}, cover: {}", agents[j].id, grid[(agents[i].y * width + agents[i].x - 1) as usize].cover);
                            if grid[(agents[i].y * width + agents[i].x - 1) as usize].cover < cover
                            {
                                cover = grid[(agents[i].y * width + agents[i].x - 1) as usize].cover;
                                shoot_id = agents[i].id;
                            }
                        }
                        else
                        {
                            if grid[(agents[i].y * width + agents[i].x + 1) as usize].cover < cover
                            {
                                cover = grid[(agents[i].y * width + agents[i].x + 1) as usize].cover;
                                shoot_id = agents[i].id;
                            }
                        }
                        
//                        wet = agents[i].wetness;
                        shoot_id = agents[i].id as i32;
                    }
                }
                if agents[j].x < 6
                {
                    if grid[((agents[j].y + 1) * width + (agents[j].x + 1)) as usize].cover > grid[((agents[j].y - 1) * width + (agents[j].x + 1)) as usize].cover
                    {
                        move_y += 1;
                    }
                    else
                    {
                        move_y -= 1;
                    }
                }
                else
                {
                    if grid[((agents[j].y + 1) * width + (agents[j].x - 1)) as usize].cover > grid[((agents[j].y - 1) * width + (agents[j].x - 1)) as usize].cover
                    {
                        move_y += 1;
                    }
                    else
                    {
                        move_y -= 1;
                    }
                }
            println!("SHOOT {}; MOVE {} {}; MESSAGE {}", shoot_id, move_x, move_y, debug);
            debug += 1;
            }
        }
    }
}
