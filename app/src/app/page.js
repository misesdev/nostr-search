import HomeHeader from '@/components/HomeHeader';
import HomeSearch from '@/components/HomeSearch';
import Image from 'next/image';

export default function Home() {
    return (
        <>
            <HomeHeader />
            <div className='flex flex-col items-center mt-22'>
                <Image
                    src='/logo.png'
                    alt='Nostr Book Users'
                    width={260}
                    height={100}
                />
                <h2
                    style={{ color: '#fff', fontSize: 26 }}
                    className='my-2 font-bold'
                >Nostr Book - Search Users</h2>
                <HomeSearch />
            </div>
        </>
    );
}
