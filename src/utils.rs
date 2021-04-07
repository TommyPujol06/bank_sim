use rand::random;

pub struct RandTable<T> {
    pub len: usize,
    pub weights: Vec<u8>,
    pub data: Box<Vec<T>>,
}

impl<T> RandTable<T>
where
    T: Copy,
{
    pub fn new(objs: &Vec<T>, weights: Vec<u8>) -> Self {
        let mut data = Vec::<T>::new();

        assert_eq!(objs.len(), weights.len());

        for (obj, &weight) in objs.iter().zip(weights.iter()) {
            for _ in 0..weight {
                data.push(*obj);
            }
        }

        let len = data.len();
        let data = Box::new(data);

        Self { len, weights, data }
    }

    pub fn random(&self) -> T {
        let rand = random::<usize>();
        self.data[rand % self.len]
    }
}
